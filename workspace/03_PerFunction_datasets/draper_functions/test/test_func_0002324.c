__gnat_to_gm_time
  (OS_Time *p_time,
   int *p_year,
   int *p_month,
   int *p_day,
   int *p_hours,
   int *p_mins,
   int *p_secs)
{
  struct tm *res;
  time_t time = (time_t) *p_time;

#ifdef _WIN32


  if (time & 1)
    time++;
#endif

#ifdef VMS
  res = localtime (&time);
#else
  res = gmtime (&time);
#endif

  if (res)
    {
      *p_year = res->tm_year;
      *p_month = res->tm_mon;
      *p_day = res->tm_mday;
      *p_hours = res->tm_hour;
      *p_mins = res->tm_min;
      *p_secs = res->tm_sec;
    }
  else
    *p_year = *p_month = *p_day = *p_hours = *p_mins = *p_secs = 0;
}
