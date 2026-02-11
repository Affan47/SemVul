WaitMS(int msec)
{
 int sec, retc, usec;
 struct timeval tnow;
 struct timespec tval;


   if (msec < 1000) sec = 0;
      else {sec = msec / 1000; msec = msec % 1000;}
   usec = msec * 1000;


   if (relMutex) Lock();


   gettimeofday(&tnow, 0);


   tval.tv_sec  = tnow.tv_sec  +  sec;
   tval.tv_nsec = tnow.tv_usec + usec;
   if (tval.tv_nsec > 1000000)
      {tval.tv_sec += tval.tv_nsec / 1000000;
       tval.tv_nsec = tval.tv_nsec % 1000000;
      }
   tval.tv_nsec *= 1000;


   do {retc = pthread_cond_timedwait(&cvar, &cmut, &tval);}
   while (retc && (retc != ETIMEDOUT));

   if (relMutex) UnLock();
   return retc == ETIMEDOUT;
}
