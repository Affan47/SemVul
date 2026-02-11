mailimf_date_time_write_driver(int (* do_write)(void *, const char *, size_t), void * data, int * col,
				   struct mailimf_date_time * date_time)
{
  int r;
  char date_str[MAX_DATE_STR];
#if 0
  struct tm tmval;
  time_t timeval;
#endif
  int wday;

#if 0
  tmval.tm_sec  = date_time->sec;
  tmval.tm_min  = date_time->min;
  tmval.tm_hour  = date_time->hour;
  tmval.tm_sec  = date_time->sec;
  tmval.tm_mday = date_time->day;
  tmval.tm_mon = date_time->month - 1;
  tmval.tm_year = date_time->year - 1900;
  tmval.tm_isdst = 1;

  timeval = mktime(&tmval);

  localtime_r(&timeval, &tmval);
#endif

  wday = dayofweek(date_time->dt_year, date_time->dt_month, date_time->dt_day);

  snprintf(date_str, MAX_DATE_STR, "%s, %i %s %i %02i:%02i:%02i %+05i",
      week_of_day_str[wday], date_time->dt_day,
      month_str[date_time->dt_month - 1],
      date_time->dt_year, date_time->dt_hour,
      date_time->dt_min, date_time->dt_sec,
      date_time->dt_zone);

  r = mailimf_string_write_driver(do_write, data, col, date_str, strlen(date_str));

  if (r != MAILIMF_NO_ERROR)
    return r;

  return MAILIMF_NO_ERROR;
}
