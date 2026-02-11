reset(void)
{
  myRobot->stop();
  myRobot->moveTo(ArPose(0, 0, 0));
  if (myGyro != NULL && !myGyro->hasNoInternalData())
    myGyroZero = myGyro->getHeading();
  myRobotZero = myRobot->getRawEncoderPose().getTh();
  myInHeadingMode = true;
  myHeading = myRobot->getTh();
}
