pause(double seconds, bool show)
{
  Timer timer;
  strstream strm;

  if ( show ) {
    strm << "---Pause " << seconds << " seconds..." << ends;
    showMsg(strm.str());
  } else {
    generateEvent();
    update();
  }

  timer.start();

  while ( timer.getLapTime(WALL_TIME) < seconds );

  if ( show ) {
    showMsg("---Pause done!...");
  } else {
    generateEvent();
    update();
  }
}
