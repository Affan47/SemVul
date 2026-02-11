laserCheckLostConnection(void)
{

  if ((myRobot == NULL || myRobotRunningAndConnected) &&
      getConnectionTimeoutSeconds() > 0 &&
      myLastReading.mSecSince() >  getConnectionTimeoutSeconds() * 1000)
    return true;

  if (!myRobotRunningAndConnected && myRobot != NULL &&
      myRobot->isRunning() && myRobot->isConnected())
  {
    myRobotRunningAndConnected = true;
    myLastReading.setToNow();
  }

  return false;
}
