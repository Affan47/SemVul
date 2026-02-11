parse_time_t (int64_t *ret, const char *str)
{
  struct tm tm;
  time_t r;

  if (STREQ (str, "0000 00 00 00:00:00.00") ||
      STREQ (str, "             :  :  .  ")) {
    *ret = -1;
    return 0;
  }

  if (sscanf (str, "%04d %02d %02d %02d:%02d:%02d",
              &tm.tm_year, &tm.tm_mon, &tm.tm_mday,
              &tm.tm_hour, &tm.tm_min, &tm.tm_sec) != 6) {
    reply_with_error ("cannot parse date from isoinfo: %s", str);
    return -1;
  }


  tm.tm_year -= 1900;
  tm.tm_mon--;
  tm.tm_isdst = -1;


  r = timegm (&tm);
  if (r == -1) {
    reply_with_error ("invalid date or time: %s", str);
    return -1;
  }

  *ret = r;
  return 0;
}
