normalize_struct_tm (struct tm* time)
{
     gint year = time->tm_year + 1900;
     gint last_day;
     time64 secs;

     ++time->tm_mon;


     if (year < 0) year = -year;
     if (year > 9999) year %= 10000;

     normalize_time_component (&(time->tm_sec), &(time->tm_min), 60, 0);
     normalize_time_component (&(time->tm_min), &(time->tm_hour), 60, 0);
     normalize_time_component (&(time->tm_hour), &(time->tm_mday), 24, 0);
     normalize_time_component (&(time->tm_mon), &year, 12, 1);
     while (time->tm_mday < 1)
     {
	  last_day = gnc_date_get_last_mday (normalize_month (--time->tm_mon), year);
	  time->tm_mday += last_day;
	  normalize_time_component (&(time->tm_mon), &year, 12, 1);
     }
     last_day = gnc_date_get_last_mday (normalize_month (time->tm_mon), year);
     while (time->tm_mday > last_day)
     {
	  ++time->tm_mon;
	  time->tm_mday -= last_day;
	  normalize_time_component (&(time->tm_mon), &year, 12, 1);
	  last_day = gnc_date_get_last_mday (normalize_month (time->tm_mon), year);
     }
     time->tm_year = year - 1900;
}
