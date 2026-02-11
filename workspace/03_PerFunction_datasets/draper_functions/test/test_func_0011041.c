SetIntervalInformation(
  int unit,
  vtkGenericStreamTracer::IntervalInformation& currentValues)
{
  if ( unit == currentValues.Unit )
    {
    return;
    }

  if ( (unit < TIME_UNIT) || (unit > CELL_LENGTH_UNIT) )
    {
    vtkWarningMacro("Unrecognized unit. Using TIME_UNIT instead.");
    currentValues.Unit = TIME_UNIT;
    }
  else
    {
    currentValues.Unit = unit;
    }

  this->Modified();
}
