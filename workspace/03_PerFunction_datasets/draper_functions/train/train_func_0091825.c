up(void)
{
  if (myExercising == true)
  {
    myExercising = false;
    myGripper.gripperHalt();
  }
  myGripper.liftUp();
}
