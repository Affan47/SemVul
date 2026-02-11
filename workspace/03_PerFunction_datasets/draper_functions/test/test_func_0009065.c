toc( void )
{
   struct timeval time;
   gettimeofday(&time, NULL);
   double newtime = time.tv_sec + ((double)time.tv_usec)/1000000.0;

   if ( lasttime == -1 )
      lasttime = newtime;

   return (float)(newtime - lasttime);
}
