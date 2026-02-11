setToNow(void)
{

#if defined(_POSIX_TIMERS) && defined(_POSIX_MONOTONIC_CLOCK)
  if (ourMonotonicClock)
  {
    struct timespec timeNow;
    if (clock_gettime(CLOCK_MONOTONIC, &timeNow) == 0)
    {


      mySec = timeNow.tv_sec + 1000000;
      myMSec = timeNow.tv_nsec / 1000000;
      return;
    }
    else
    {
      ourMonotonicClock = false;
      ArLog::logNoLock(ArLog::Terse, "ArTime::setToNow: invalid return from clock_gettime.");
    }
  }
#endif

#ifndef WIN32
  struct timeval timeNow;

  if (gettimeofday(&timeNow, NULL) == 0)
  {


    mySec = timeNow.tv_sec + 1000000;
    myMSec = timeNow.tv_usec / 1000;
  }
  else
    ArLog::logNoLock(ArLog::Terse, "ArTime::setToNow: invalid return from gettimeofday.");

#else


  long timeNow;
  timeNow = timeGetTime();


  mySec = timeNow / 1000 + 1000000;
  myMSec = timeNow % 1000;

#endif

}
