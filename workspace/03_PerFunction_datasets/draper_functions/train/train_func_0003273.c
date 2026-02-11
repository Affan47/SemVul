getClosestBoxInList(
	double x1, double y1, double x2, double y2, ArPose startPos,
	unsigned int maxRange, ArPose *readingPos, ArPose targetPose,
	const std::list<ArPoseWithTime *> *buffer)

{
  double closest;
  double dist;
  ArPose closestPos;
  std::list<ArPoseWithTime *>::const_iterator it;
  ArTransform trans;
  ArPoseWithTime pose;
  ArPose zeroPos;

  double temp;

  closest = maxRange;
  zeroPos.setPose(0, 0, 0);
  trans.setTransform(startPos, zeroPos);

  if (x1 >= x2)
  {
    temp = x1,
    x1 = x2;
    x2 = temp;
  }
  if (y1 >= y2)
  {
    temp = y1,
    y1 = y2;
    y2 = temp;
  }

  for (it = buffer->begin(); it != buffer->end(); ++it)
  {
    pose = trans.doTransform(*(*it));


    if (pose.getX() >= x1 && pose.getX() <= x2 &&
	pose.getY() >= y1 && pose.getY() <= y2)
    {
      dist = pose.findDistanceTo(targetPose);

      if (dist < closest)
      {
	closest = dist;
	closestPos = pose;
      }
    }
  }
  if (readingPos != NULL)
    *readingPos = closestPos;
  if (closest > maxRange)
    return maxRange;
  else
    return closest;
}
