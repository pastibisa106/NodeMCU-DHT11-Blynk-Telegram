//library blynk
#define BLYNK_PRINT Serial
#include <SPI.h>
#include <SimpleTimer.h>

//library DHT
#include <DHT.h>
#define DHTPIN 2  // GPIO D4
#define DHTTYPE DHT11 // dht22
DHT dht (DHTPIN, DHTTYPE);

//library ESP8266
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

SimpleTimer timer;

char auth[] = "c8HqLVcjRdrvoUO3plcaDWEYOkE4OuSx"; //get token from blynk app android
char ssid[] = "HUAWEI"; // ssid wifi
char pass[] = "pastibisa"; //password wifi

void sendSensor () {
    float h = dht.readHumidity();
    float t = dht.readTemperature(); // or dht.readTemperature(true) for Fahrenheit
    if (isnan(h) || isnan(t)) {
        Serial.println("Failed to read from DHT sensor!");
        return;
    }
    Blynk.virtualWrite(V0, t); // V6 for temperature
    Blynk.virtualWrite(V1, h); // V5 for humidity
}

void setup() {
    Serial.begin(9600);
    Blynk.begin(auth, ssid, pass);
    dht.begin();
    timer.setInterval(1000L, sendSensor);
    Serial.println("\n");
}

void loop() {
    Blynk.run();
    timer.run(); // initiates SimpleTimer
    float h = dht.readHumidity();
    float t = dht.readTemperature(); // or dht.readTemperature(true) for Fahrenheit
    Serial.print("Suhu: ");
    Serial.print(t);
    Serial.print("°C ");
    Serial.print("\t");
    Serial.print("RH: ");
    Serial.print(h);
    Serial.println("%");
    delay(1000);
}
