sge_relative_timespec(signed long timeout, struct timespec *ts)
{
   struct timeval now;


   gettimeofday(&now, NULL);
   ts->tv_sec = now.tv_sec;
   ts->tv_nsec = now.tv_usec * 1000;

   if (timeout != 0)
      ts->tv_sec += timeout;


   return;
}
