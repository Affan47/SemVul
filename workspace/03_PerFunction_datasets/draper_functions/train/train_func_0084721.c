helpMovementKeys(void)
{
  ArLog::log(ArLog::Terse,
	     "Camera mode will now let you move the camera.");
  ArLog::log(ArLog::Terse, "%13s:  tilt camera up by %d", "up arrow", myTiltAmount);
  ArLog::log(ArLog::Terse, "%13s:  tilt camera down by %d", "down arrow", myTiltAmount);
  ArLog::log(ArLog::Terse, "%13s:  pan camera left by %d", "left arrow", myPanAmount);
  ArLog::log(ArLog::Terse, "%13s:  pan camera right by %d", "right arrow", myPanAmount);
  ArLog::log(ArLog::Terse, "%13s:  center camera and zoom out",
	     "space bar");
  ArLog::log(ArLog::Terse, "%13s:  exercise the camera", "'e' or 'E'");
  if (myCam->canZoom())
  {
    ArLog::log(ArLog::Terse, "%13s:  zoom in", "'z' or 'Z'");
    ArLog::log(ArLog::Terse, "%13s:  zoom out", "'x' or 'X'");
  }
}
