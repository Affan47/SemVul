userTask(void)
{

  if (myRobot->isTryingToMove() || fabs(myRobot->getVel()) > 3 ||
      fabs(myRobot->getRotVel()) > 3)
  {
    myLastMoved.setToNow();


    if (!mySonarEnabled && myRobot->areMotorsEnabled())
    {
      mySonarEnabled = true;
      myRobot->enableSonar();
    }
  }
  else
  {


    if (mySonarEnabled && myLastMoved.secSince() > 10)
    {
      mySonarEnabled = false;
      myRobot->disableSonar();
    }
  }
}
