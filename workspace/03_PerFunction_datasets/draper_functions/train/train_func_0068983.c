httpGetDateTime(const char *s)
{
  int		i;
  char		mon[16];
  int		day, year;
  int		hour, min, sec;
  int		days;
  static const int normal_days[] =
		{ 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365 };
  static const int leap_days[] =
		{ 0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335, 366 };


  DEBUG_printf(("httpGetDateTime(s=\"%s\")\n", s));


  if (sscanf(s, "%*s%d%15s%d%d:%d:%d", &day, mon, &year, &hour, &min, &sec) < 6)
    return (0);

  DEBUG_printf(("    day=%d, mon=\"%s\", year=%d, hour=%d, min=%d, sec=%d\n",
                day, mon, year, hour, min, sec));


  for (i = 0; i < 12; i ++)
    if (!strcasecmp(mon, http_months[i]))
      break;

  if (i >= 12)
    return (0);

  DEBUG_printf(("    i=%d\n", i));


  if ((year & 3) == 0 && ((year % 100) != 0 || (year % 400) == 0))
    days = leap_days[i] + day - 1;
  else
    days = normal_days[i] + day - 1;

  DEBUG_printf(("    days=%d\n", days));

  days += (year - 1970) * 365 +
          ((year - 1) / 4 - 492) -
	  ((year - 1) / 100 - 19) +
          ((year - 1) / 400 - 4);

  DEBUG_printf(("    days=%d\n", days));

  return (days * 86400 + hour * 3600 + min * 60 + sec);
}
