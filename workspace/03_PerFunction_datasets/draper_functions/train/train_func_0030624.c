_ticker(void *data)
{
   ELM_CLOCK_DATA_GET(data, sd);

   double t;
   struct timeval timev;
   struct tm *tm;
   time_t tt;

   gettimeofday(&timev, NULL);
   t = ((double)(1000000 - timev.tv_usec)) / 1000000.0;
   sd->ticker = ecore_timer_add(t, _ticker, data);
   if (!sd->edit)
     {
        tt = (time_t)(timev.tv_sec) + sd->timediff;
        tzset();
        tm = localtime(&tt);
        if (tm)
          {
             sd->hrs = tm->tm_hour;
             sd->min = tm->tm_min;
             sd->sec = tm->tm_sec;
             _time_update(data);
          }
     }

   return ECORE_CALLBACK_CANCEL;
}
