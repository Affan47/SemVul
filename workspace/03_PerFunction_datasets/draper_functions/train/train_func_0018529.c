exercise(void)
{
  if (myExercising == false)
  {
    ArLog::log(ArLog::Terse,
       "Camera will now be exercised until another command is given.");
    myExercising = true;
    myExerState = UP_LEFT;
    myLastExer.setToNow();
    myCam->panTilt(myCam->getMaxNegPan(), myCam->getMaxPosTilt());
    myLastExerZoomed.setToNow();
    myExerZoomedIn = true;
    if (myCam->canZoom())
      myCam->zoom(myCam->getMaxZoom());
  }
}
