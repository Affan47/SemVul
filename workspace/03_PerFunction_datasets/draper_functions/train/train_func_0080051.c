kwsysProcessGetTimeoutTime(kwsysProcess* cp, double* userTimeout,
                                      kwsysProcessTime* timeoutTime)
{


  if(cp->Timeout > 0 && cp->TimeoutTime.tv_sec < 0)
    {
    kwsysProcessTime length = kwsysProcessTimeFromDouble(cp->Timeout);
    cp->TimeoutTime = kwsysProcessTimeAdd(cp->StartTime, length);
    }


  *timeoutTime = cp->TimeoutTime;


  if(userTimeout)
    {
    kwsysProcessTime currentTime = kwsysProcessTimeGetCurrent();
    kwsysProcessTime userTimeoutLength = kwsysProcessTimeFromDouble(*userTimeout);
    kwsysProcessTime userTimeoutTime = kwsysProcessTimeAdd(currentTime,
                                                           userTimeoutLength);
    if(timeoutTime->tv_sec < 0 ||
       kwsysProcessTimeLess(userTimeoutTime, *timeoutTime))
      {
      *timeoutTime = userTimeoutTime;
      return 1;
      }
    }
  return 0;
}
