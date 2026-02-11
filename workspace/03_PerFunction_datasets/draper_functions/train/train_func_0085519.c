timestamp (const ACE_Time_Value& time_value,
                ACE_TCHAR date_and_time[],
                size_t date_and_timelen,
                bool return_pointer_to_first_digit)
{


  if (date_and_timelen < 27)
    {
      errno = EINVAL;
      return 0;
    }

  ACE_Time_Value cur_time =
    (time_value == ACE_Time_Value::zero) ?
        ACE_Time_Value (ACE_OS::gettimeofday ()) : time_value;
  time_t secs = cur_time.sec ();
  struct tm tms;
  ACE_OS::localtime_r (&secs, &tms);
  ACE_OS::snprintf (date_and_time,
                    date_and_timelen,
                    ACE_TEXT ("%4.4d-%2.2d-%2.2d %2.2d:%2.2d:%2.2d.%06ld"),
                    tms.tm_year + 1900,
                    tms.tm_mon + 1,
                    tms.tm_mday,
                    tms.tm_hour,
                    tms.tm_min,
                    tms.tm_sec,
                    static_cast<long> (cur_time.usec()));
  date_and_time[date_and_timelen - 1] = '\0';
  return &date_and_time[11 + (return_pointer_to_first_digit != 0)];
}
