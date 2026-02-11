pmMeasureExtBatteryVoltage(void)
{
  float voltage;

  if (extBatVoltDeckPin)
  {
    voltage = analogReadVoltage(extBatVoltDeckPin) * extBatVoltMultiplier;
  }
  else
  {
    voltage = 0.0;
  }

  return voltage;
}
