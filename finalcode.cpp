int pinforled = 12;
float minimumvalueofLDR = 400;
int min_voltage_solarpanel = 10;
float LDRreading;
float live_solarpanel_reading;
void setup() // default set up function
{
  Serial.begin(9600);
  pinMode(pinforled, OUTPUT); // allocating location for led
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW); // turning it off right in the start
  digitalWrite(pinforled, LOW);
  pinMode(A0, INPUT); // allocating location for data input of LDR reading
}

float Light(int RawADC0) // function to convert LDR reading into lux unit
{
  double Vout = RawADC0 * 0.0048828125;
  float lux = (2500 / Vout - 500) / 10;
  return lux;
}

void loop() // A default function built within arduino which would work over and over again in real life
{

  delay(500);
  LDRreading = float(Light(analogRead(A0))); // taking input from the LDR sensor
  live_solarpanel_reading = analogRead(A4);  // reading of output from solar panel

  if (live_solarpanel_reading < min_voltage_solarpanel)
  {                                     // we are not getting sufficient energy from the solar panel so we'll check the condition
    if (LDRreading < minimumvalueofLDR) // to check the presence of sun
    {

      Serial.print("Light Intensity in Lux : "); // printing the light intensity
      Serial.println(LDRreading);                // printing LDR reading
      // sun is present yet we are not getting enough output from the solar panel therefore there must exist some dirt on the solar panel
      digitalWrite(pinforled, HIGH); // so we'll turn on the light indicating we started sprinkling water
    }
    else
    {
      // sun is not present so no need to check further
      // everything is working fine
      Serial.print("Light Intensity in Lux : "); // printing the light intensity
      Serial.println(LDRreading);                // printing LDR reading
      digitalWrite(pinforled, LOW);              // we'll turn off the light indicating we started sprinkling water
    }
  }
  else
  {
    // we are getting enough solar power from the panel so we dont need to do anything
    Serial.println("Solar panel is working efficiently");
    digitalWrite(LED_BUILTIN, LOW);
    digitalWrite(pinforled, LOW);
  }
}
