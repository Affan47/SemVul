startPeriodicUpdate(int refreshFrequency, ArLog::LogLevel logLevel)
{
  ourCPUMutex.setLogName("ArSystemStatusRefreshThread::ourCPUMutex");
  ourWirelessMutex.setLogName("ArSystemStatusRefreshThread::ourWirelessMutex");

  if(ourPeriodicUpdateThread) {

    ourPeriodicUpdateThread->setRefreshFreq(refreshFrequency);
    ourPeriodicUpdateThread->setLogLevel(logLevel);
    return;
  }

  ourPeriodicUpdateThread = new ArSystemStatusRefreshThread(refreshFrequency);
  ourPeriodicUpdateThread->setLogLevel(logLevel);
  ourPeriodicUpdateThread->runAsync();
}
