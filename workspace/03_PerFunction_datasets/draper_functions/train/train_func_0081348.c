isotime2seconds (const char *string)
{
  const char *s;
  int year, month, day, hour, minu, sec;
  struct tm tmbuf;
  int i;
  time_t result;

  if (!*string)
    return 0;
  for (s=string, i=0; i < 8; i++, s++)
    if (!digitp (s))
      return 0;
  if (*s != 'T')
      return 0;
  for (s++, i=9; i < 15; i++, s++)
    if (!digitp (s))
      return 0;
  if ( !(!*s || (isascii (*s) && isspace(*s)) || *s == ':' || *s == ','))
    return 0;

  year  = atoi_4 (string);
  month = atoi_2 (string + 4);
  day   = atoi_2 (string + 6);
  hour  = atoi_2 (string + 9);
  minu  = atoi_2 (string + 11);
  sec   = atoi_2 (string + 13);


  if (year < 1970 || month < 1 || month > 12 || day < 1 || day > 31
      || hour > 23 || minu > 59 || sec > 61 )
    return 0;

  memset (&tmbuf, 0, sizeof tmbuf);
  tmbuf.tm_sec  = sec;
  tmbuf.tm_min  = minu;
  tmbuf.tm_hour = hour;
  tmbuf.tm_mday = day;
  tmbuf.tm_mon  = month-1;
  tmbuf.tm_year = year - 1900;
  tmbuf.tm_isdst = -1;
  result = timegm (&tmbuf);
  return (result == (time_t)(-1))? 0 : (u32)result;
}
