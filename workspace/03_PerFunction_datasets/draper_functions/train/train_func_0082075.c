runThread(void *arg)
{
  MRPT_UNUSED_PARAM(arg);
  threadStarted();

  long timeToSleep;
  ArTime loopEndTime;
  std::list<ArFunctor *> *runList;
  std::list<ArFunctor *>::iterator iter;
  ArTime lastLoop;
  bool firstLoop = true;
  bool warned = false;

  if (!myRobot)
  {
    ArLog::log(ArLog::Terse, "ArSyncLoop::runThread: Trying to run the synchronous loop without a robot.");
    return(0);
  }

  if (!myRobot->getSyncTaskRoot())
  {
    ArLog::log(ArLog::Terse, "ArSyncLoop::runThread: Can not run the synchronous loop without a task tree");
    return(0);
  }

  while (myRunning)
  {

    myRobot->lock();
    if (!firstLoop && !warned && !myRobot->getNoTimeWarningThisCycle() &&
	myRobot->getCycleWarningTime() != 0 &&
	lastLoop.mSecSince() > (signed int) myRobot->getCycleWarningTime())
    {
      ArLog::log(ArLog::Normal,
 "Warning: ArRobot cycle took too long because the loop was waiting for lock.");
      ArLog::log(ArLog::Normal,
		 "\tThe cycle took %u ms, (%u ms normal %u ms warning)",
		 lastLoop.mSecSince(), myRobot->getCycleTime(),
		 myRobot->getCycleWarningTime());
    }
    myRobot->setNoTimeWarningThisCycle(false);
    firstLoop = false;
    warned = false;
    lastLoop.setToNow();

    loopEndTime.setToNow();
    loopEndTime.addMSec(myRobot->getCycleTime());
    myRobot->incCounter();
    myRobot->unlock();


    myRobot->getSyncTaskRoot()->run();
    if (myStopRunIfNotConnected && !myRobot->isConnected())
    {
      if (myRunning)
	ArLog::log(ArLog::Normal, "Exiting robot run because of lost connection.");
      break;
    }
    timeToSleep = loopEndTime.mSecTo();


    if (myRobot->isCycleChained() && myRobot->isConnected())
      timeToSleep = 0;

    if (!myRobot->getNoTimeWarningThisCycle() &&
	myRobot->getCycleWarningTime() != 0 &&
	lastLoop.mSecSince() > (signed int) myRobot->getCycleWarningTime())
    {
      ArLog::log(ArLog::Normal,
	"Warning: ArRobot sync tasks too long at %u ms, (%u ms normal %u ms warning)",
		 lastLoop.mSecSince(), myRobot->getCycleTime(),
		 myRobot->getCycleWarningTime());
      warned = true;
    }


    if (timeToSleep > 0)
      ArUtil::sleep(timeToSleep);
  }
  myRobot->lock();
  myRobot->wakeAllRunExitWaitingThreads();
  myRobot->unlock();

  myRobot->lock();
  runList=myRobot->getRunExitListCopy();
  myRobot->unlock();
  for (iter=runList->begin();
       iter != runList->end(); ++iter)
    (*iter)->invoke();
  delete runList;

  return(0);
}
