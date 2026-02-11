setIncrement(double increment)
{
  if (!myCanSetIncrement)
  {
    ArLog::log(ArLog::Terse, "%s::setIncrement: Cannot set increment on this laser", myName.c_str());
    return false;
  }

  if (increment < myIncrementMin)
  {
    ArLog::log(ArLog::Terse, "%s::setIncrement: Increment (%g) tried to be set to less than the minimum (%g))", myName.c_str(), increment, myIncrementMin);
    return false;
  }
  if (increment > myIncrementMax)
  {
    ArLog::log(ArLog::Terse, "%s::setIncrement: End degrees (%g) tried to be set to greater than the maximum (%g))", myName.c_str(), increment, myIncrementMax);
    return false;
  }
  myIncrementSet = true;
  myIncrement = increment;
  return true;
}
