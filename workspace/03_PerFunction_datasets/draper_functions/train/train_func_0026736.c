getRemoteIsSim(void) const
{
  if (myRemoteIsSim)
    return true;
  else if (myRemoteIsNotSim)
    return false;
  else if (myRobot != NULL &&
	   strcasecmp(myRobot->getRobotName(), "MobileSim") == 0)
    return true;
  else
    return false;
}
