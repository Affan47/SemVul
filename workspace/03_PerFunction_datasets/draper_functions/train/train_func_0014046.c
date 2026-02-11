mailimf_get_date(time_t t)
{
  struct tm gmt;
  struct tm lt;
  int off;
  struct mailimf_date_time * date_time;

  if (gmtime_r(&t, &gmt) == NULL)
    return NULL;

  if (localtime_r(&t, &lt) == NULL)
    return NULL;

  off = (mail_mkgmtime(&lt) - mail_mkgmtime(&gmt)) * 100 / (60 * 60);

  date_time = mailimf_date_time_new(lt.tm_mday, lt.tm_mon + 1, lt.tm_year + 1900,
				    lt.tm_hour, lt.tm_min, lt.tm_sec,
				    off);

  return date_time;
}
