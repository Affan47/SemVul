callbackSleepBetweenCheckpoint ( int sec )
{
  dmtcp::ThreadSync::waitForUserThreadsToFinishPreResumeCB();
  dmtcp_process_event(DMTCP_EVENT_WAIT_FOR_SUSPEND_MSG, NULL);
  dmtcp::DmtcpWorker::instance().waitForStage1Suspend();

  prctlGetProcessName();
  unmapRestoreArgv();

  dmtcp_process_event(DMTCP_EVENT_GOT_SUSPEND_MSG,
                      (void*) dmtcp::VirtualPidTable::instance().numThreads());


  JALIB_CKPT_LOCK();
}
