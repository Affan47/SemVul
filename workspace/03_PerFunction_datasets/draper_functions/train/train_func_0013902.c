shaper_soonest_event (struct timeval *tv, int delay)
{
  bool ret = false;
  if (delay < 1000000)
    {
      if (tv->tv_sec)
	{
	  tv->tv_sec = 0;
	  tv->tv_usec = delay;
	  ret = true;
	}
      else if (delay < tv->tv_usec)
	{
	  tv->tv_usec = delay;
	  ret = true;
	}
    }
  else
    {
      const int sec = delay / 1000000;
      const int usec = delay % 1000000;

      if (sec < tv->tv_sec)
	{
	  tv->tv_sec = sec;
	  tv->tv_usec = usec;
	  ret = true;
	}
      else if (sec == tv->tv_sec)
	{
	  if (usec < tv->tv_usec)
	    {
	      tv->tv_usec = usec;
	      ret = true;
	    }
	}
    }
#ifdef SHAPER_DEBUG
  dmsg (D_SHAPER_DEBUG, "SHAPER shaper_soonest_event sec=%d usec=%d ret=%d",
       (int)tv->tv_sec, (int)tv->tv_usec, (int)ret);
#endif
  return ret;
}
