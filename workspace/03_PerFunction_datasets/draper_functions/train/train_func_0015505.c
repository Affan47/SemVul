setParams(
	double startingDegrees, double endingDegrees,
	double incrementDegrees, bool flipped)
{
  if (startingDegrees < -180.0 || startingDegrees > 180.0 ||
      endingDegrees < -180.0 || startingDegrees > 180.0 ||
      incrementDegrees < 0.0)
  {
    ArLog::log(ArLog::Normal,
	       "%s::setParams: Bad params (starting %g ending %g incrementDegrees %g)",
	       getName(), startingDegrees, endingDegrees, incrementDegrees);
    return false;
  }
  double startingStepRaw;
  double endingStepRaw;
  int startingStep;
  int endingStep;
  int clusterCount;


  startingStepRaw = -(startingDegrees - myStepFirst) / myStepSize;

  endingStepRaw = -(endingDegrees - myStepFirst) / myStepSize;
  startingStep = (int)ceil(ArUtil::findMin(startingStepRaw, endingStepRaw));
  endingStep = (int)floor(ArUtil::findMax(startingStepRaw, endingStepRaw));

  clusterCount = ArMath::roundInt(incrementDegrees / myStepSize);
  if (clusterCount < 1)
    clusterCount = 1;

  ArLog::LogLevel logLevel;
  if (myLogMore)
    logLevel = ArLog::Normal;
  else
    logLevel = ArLog::Verbose;

  ArLog::log(logLevel, "%s: starting deg %.1f raw %.1f step %d ending deg %.1f raw %.1f step %d, cluster deg %f count %d flipped %d",
	     getName(), startingDegrees, startingStepRaw, startingStep, endingDegrees, endingStepRaw, endingStep, incrementDegrees, clusterCount, flipped);

  return setParamsBySteps(startingStep, endingStep, clusterCount, flipped);
}
