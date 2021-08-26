#include <Arduino_LSM9DS1.h>

const float acceleration_threshold = 2.5;
const int num_samples = 119;

int samples_read = num_samples;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  while (!Serial);

  if(!IMU.begin()){
    Serial.println("fail to initialize IMU");
    while (1);
    }

  Serial.println("aX,aY,aZ,gX,gY,gZ");
}

void loop() {
  // put your main code here, to run repeatedly:
  float aX, aY, aZ, gX, gY, gZ;
  while (samples_read == num_samples){
    if(IMU.accelerationAvailable()){
      IMU.readAcceleration(aX, aY, aZ);
      float aSum = fabs(aX) + fabs(aY) + fabs(aZ);
      if (aSum >= acceleration_threshold){
        samples_read = 0;
        break;
        }
      }
    }

  while (samples_read < num_samples) {
    if (IMU.accelerationAvailable()&&IMU.gyroscopeAvailable()) {
      IMU.readAcceleration(aX,aY,aZ);
      IMU.readGyroscope(gX,gY,gZ);
      samples_read = samples_read + 1;

       Serial.print(aX,3); // in CSV
       Serial.print(',');
       Serial.print(aY,3);
       Serial.print(',');
       Serial.print(aZ,3);
       Serial.print(',');
       Serial.print(gX,3);
       Serial.print(',');
       Serial.print(gY,3);
       Serial.print(',');
       Serial.print(gZ,3);
       Serial.println();

       if (samples_read == num_samples){
        Serial.println();
        }
      }
    }
}
