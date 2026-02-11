runAsync(bool stopRunIfNotConnected, bool runNonThreadedPacketReader)
{
  if (mySyncLoop.getRunning())
  {
    ArLog::log(ArLog::Terse,
	       "The robot is already running, cannot run it again.");
    return;
  }
  if (runNonThreadedPacketReader)
  {
    mySyncLoop.stopRunIfNotConnected(stopRunIfNotConnected);


    mySyncLoop.create(true, false);
    myRunningNonThreaded = true;
  }
  else
  {
    myRunningNonThreaded = false;


    mySyncLoop.create(true, true);


    myPacketReader.create(true, false);
  }
}
