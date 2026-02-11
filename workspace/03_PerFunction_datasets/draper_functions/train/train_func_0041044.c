adjustRawReadings(bool interlaced)
{
  std::list<ArSensorReading *>::iterator rawIt;


  if (myRawReadings == NULL || myRobot == NULL ||
      (myAdjustedRawReadings == NULL && myRobot->getOdometryDelay() == 0))
    return;


  if (myAdjustedRawReadings == NULL)
    myAdjustedRawReadings = new std::list<ArSensorReading *>;


  if (myRawReadings->begin() != myRawReadings->end() &&
      myRawReadings->front()->getAdjusted())
    return;

  std::list<ArSensorReading *>::iterator adjIt;
  ArSensorReading *adjReading;
  ArSensorReading *rawReading;

  ArTransform trans;
  ArTransform encTrans;
  ArTransform interlacedTrans;
  ArTransform interlacedEncTrans;

  bool first = true;
  bool second = true;

  int onReading;
  for (rawIt = myRawReadings->begin(), adjIt = myAdjustedRawReadings->begin(),
       onReading = 0;
       rawIt != myRawReadings->end();
       rawIt++, onReading++)
  {
    rawReading = (*rawIt);
    if (adjIt != myAdjustedRawReadings->end())
    {
      adjReading = (*adjIt);
      adjIt++;
    }
    else
    {
      adjReading = new ArSensorReading;
      myAdjustedRawReadings->push_back(adjReading);
    }
    (*adjReading) = (*rawReading);
    if (first || (interlaced && second))
    {
      ArPose origPose;
      ArPose corPose;
      ArPose origEncPose;
      ArPose corEncPose;
      ArTime corTime;


      corTime = rawReading->getTimeTaken();
      corTime.addMSec(-myRobot->getOdometryDelay());
      if (myRobot->getPoseInterpPosition(corTime,
					 &corPose) == 1 &&
	  myRobot->getEncoderPoseInterpPosition(corTime,
						&corEncPose) == 1)
      {
	origPose = rawReading->getPoseTaken();
	origEncPose = rawReading->getEncoderPoseTaken();


	if (first)
	{
	  trans.setTransform(origPose, corPose);
	  encTrans.setTransform(origEncPose, corEncPose);
	}
	else if (interlaced && second)
	{
	  interlacedTrans.setTransform(origPose, corPose);
	  interlacedEncTrans.setTransform(origEncPose, corEncPose);
	}
      }
      else
      {

      }

      if (first)
	first = false;
      else if (interlaced && second)
	second = false;

    }
    if (!interlaced && (onReading % 2) == 0)
    {
      adjReading->applyTransform(trans);
      adjReading->applyEncoderTransform(encTrans);
    }
    else
    {
      adjReading->applyTransform(interlacedTrans);
      adjReading->applyEncoderTransform(interlacedEncTrans);
    }


    adjReading->setAdjusted(true);
    rawReading->setAdjusted(true);
  }
}
