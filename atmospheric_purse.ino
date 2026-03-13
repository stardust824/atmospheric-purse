#include <stdio.h>
#include <Wire.h>
#define Wire Wire1
#include <LiquidCrystal_I2C.h>
#include <WiFi.h>
#include <SPI.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

#define SUNNY 1
#define RAINY 2
#define SNOWY 3

void getData();
void setup();
void loop();

int button = 1;
int buzzer = 2;
int screen = 3;

// const char* ssid = "Colon Three";
// const char* pass = "RawrxDcolon3";
const char* ssid = "Neil's Android";
const char* pass = "supboii4";
char server[] = "api.weather.gov";
WiFiClient client;
HTTPClient https;



LiquidCrystal_I2C display(0x27, 16, 2);


void setup() {
  pinMode(button, INPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(screen, OUTPUT);
  // enable pull up resistor
  digitalWrite(button, HIGH);
  Wire1.setSDA(2);
  Wire1.setSCL(3);
  Wire1.begin();
  display.init();
  Serial.begin(9600);
  display.backlight();

  WiFi.begin(ssid, pass);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("connected!");
  Serial.println(WiFi.localIP());

  // for (int i = 0; i < 25; i++) {
    // Serial.println("GRRR");
    // Serial.println(i);
    // delay(1000);
  // }
  while (1) {
    if (Serial.available()) {
      if (Serial.read() == 'a') {
        break;
      }
    }
  }

  Serial.println("START");

  https.setInsecure();  // Use certs, but do not check their authenticity
  // maybe need to include client in args here
  https.useHTTP10(true);
  if (https.begin("https://api.weather.gov/gridpoints/SEW/131,122/forecast")) {
    // times out unless this is included
    https.addHeader("Accept", "*/*");
    // need this to connect and get real data
    https.setUserAgent("Stwawbewwy");

    Serial.println("Connected to server");
    if (https.GET() > 0) {
      // parses response
      DynamicJsonDocument doc(2048);
      deserializeJson(doc, https.getStream());
      // Read values
      Serial.println("Temp: ");
      Serial.println(doc["properties"]["periods"][0]["temperature"].as<long>());
      Serial.println("Rain percent: ");
      Serial.println(doc["properties"]["periods"][0]["probabilityOfPrecipitation"]["value"].as<long>());
      Serial.println("Temp: ");
      Serial.println(doc["properties"]["periods"][1]["temperature"].as<long>());
    } else {
      Serial.println("nope!!");
    }
    https.end();
  }

  //if (client.connect(server, 80)) {

    //Serial.println("connected to server");

    // Make a HTTP request:

    //client.println("GET /gridpoints/SEW/131,122/forecast HTTP/1.1");

    //client.println("Host: api.weather.gov");

    //client.println("Connection: close");

    //client.println();

  //}
  //getData();

  // weather url https://api.weather.gov/gridpoints/SEW/131,122/forecast
  // if can't connect to WiFi,
    // display error on screen
  // else
    // grab weather data
   // int high = // weather high
    //int low = // weather low
    //int type_of_weather = // weather
    // if wind > 10mph, 
      // turn on wind light
    // display high and low on screen
}

void loop() {

  if (Serial.available()) {
    if (Serial.read() == 'b') {
      rp2040.rebootToBootloader();
    }
  }

  //display.setBacklight(0);
  display.print("hello world");
  //Serial.println("I2C scan:");
  //for (uint8_t addr = 1; addr < 127; addr++) {
   // Wire1.beginTransmission(addr);
    //if (Wire1.endTransmission() == 0) {
     // Serial.print("Found device at 0x");
    //  if (addr < 16) Serial.print("0");
    //  Serial.println(addr, HEX);
   //  delay(5);
   // }
  //}


  

  //if (digitalRead(button) == 0) {
    //if (type_of_weather == SUNNY) {
      // play "You Are My Sunshine"
    //}
  //} else if (type_of_weather == RAINY) {
    // play It's Raining Men
 //} else if (type_of_weather == SNOWY) {
    // play Frosty the Snowman
  //} else {
    // display error on screen
  //}
}

