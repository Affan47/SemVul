SpinSleep(int Microseconds)
{
   struct timeval StartTime;
   int Delta;

   GetTimeNow();
   StartTime = TimeNow;
   for( ; ; ) {
      GetTimeNow();
      Delta = ((TimeNow.tv_sec - StartTime.tv_sec) * 1000000) +
               TimeNow.tv_usec - StartTime.tv_usec;
      if(Delta >= Microseconds) {
         break;
      }
   }
}
