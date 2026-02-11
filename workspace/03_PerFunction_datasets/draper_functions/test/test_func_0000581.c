getClosestPolarInList(
	double startAngle, double endAngle, ArPose startPos,
	unsigned int maxRange, double *angle,
	const std::list<ArPoseWithTime *> *buffer)
{
  double closest=0;
  bool foundOne = false;
  std::list<ArPoseWithTime *>::const_iterator it;
  ArPoseWithTime *reading;
  double th;
  double closeTh=0;
  double dist;
  double angle1, angle2;

  startAngle = ArMath::fixAngle(startAngle);
  endAngle = ArMath::fixAngle(endAngle);

  for (it = buffer->begin(); it != buffer->end(); ++it)
  {
    reading = (*it);

    angle1=startPos.findAngleTo(*reading);
    angle2=startPos.getTh();
    th = ArMath::subAngle(angle1, angle2);
    if (ArMath::angleBetween(th, startAngle, endAngle))
    {
      if (!foundOne || (dist = reading->findDistanceTo(startPos)) < closest)
      {
	closeTh = th;
	if (!foundOne)
	  closest = reading->findDistanceTo(startPos);
	else
	  closest = dist;
	foundOne = true;
      }
    }
  }
  if (!foundOne)
    return maxRange;
  if (angle != NULL)
    *angle = closeTh;
  if (closest > maxRange)
    return maxRange;
  else
    return closest;
}
