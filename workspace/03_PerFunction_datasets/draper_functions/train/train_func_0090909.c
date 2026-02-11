parseTime(const char *str, bool *ok, bool toToday)
{

  struct tm tmOut;
  if (toToday)
  {
    struct tm now;
    if (!localtime(&now))
    {
      *ok = false;
      return 0;
    }
    memcpy(&tmOut, &now, sizeof(now));
  }
  else
  {
    memset(&tmOut, 0, sizeof(tmOut));

    tmOut.tm_mday = 1;


    tmOut.tm_year = 70;
    tmOut.tm_isdst = -1;
  }

  bool isValid = true;
  int hrs = -1;
  int min = -1;
  int sec = 0;

  ArArgumentBuilder separator(512, ':');
  separator.add(str);


  if ((separator.getArgc() != 2 && separator.getArgc() != 3) ||
      !separator.isArgInt(0) || !separator.isArgInt(1) ||
      (separator.getArgc() == 3 && !separator.isArgInt(2)))
  {


    isValid = false;
  }
  else
  {
    hrs = separator.getArgInt(0);
    min = separator.getArgInt(1);
    if (separator.getArgc() == 3)
      sec = separator.getArgInt(2);

  }


  if (!((hrs  >= 0) && (hrs < 24) && (min >= 0) && (min < 60) &&
	(sec >= 0) && (sec < 60)))
    isValid = false;

  if (isValid)
  {
    tmOut.tm_hour = hrs;
    tmOut.tm_min  = min;
    tmOut.tm_sec  = sec;
  }

  time_t newTime = mktime(&tmOut);

  if (ok != NULL)
  {
    *ok = (isValid && (newTime != -1));
  }


  return newTime;

}
