signal()
{
  if (myFailedInit)
  {
    ArLog::log(ArLog::Terse, "ArCondition::signal: Initialization of condition failed, failed to signal");
    return(STATUS_FAILED_INIT);
  }

  if (pthread_cond_signal(&myCond) != 0)
  {
    ArLog::log(ArLog::Terse, "ArCondition::signal: Unknown error while trying to signal the condition.");
    return(STATUS_FAILED);
  }

  return(0);
}
