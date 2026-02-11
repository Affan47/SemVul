_gnutls_x509_time2gtime (const char *ttime, int year)
{
  char xx[4];
  struct fake_tm etime;
  time_t ret;

  if (strlen (ttime) < 8)
    {
      gnutls_assert ();
      return (time_t) - 1;
    }

  etime.tm_year = year;


  if (sizeof (time_t) <= 4 && etime.tm_year >= 2038)
    return (time_t) 2145914603;

  if (etime.tm_year < 1970)
    return (time_t) 0;

  xx[2] = 0;


  memcpy (xx, ttime, 2);
  etime.tm_mon = atoi (xx) - 1;
  ttime += 2;


  memcpy (xx, ttime, 2);
  etime.tm_mday = atoi (xx);
  ttime += 2;


  memcpy (xx, ttime, 2);
  etime.tm_hour = atoi (xx);
  ttime += 2;


  memcpy (xx, ttime, 2);
  etime.tm_min = atoi (xx);
  ttime += 2;

  if (strlen (ttime) >= 2)
    {
      memcpy (xx, ttime, 2);
      etime.tm_sec = atoi (xx);
      ttime += 2;
    }
  else
    etime.tm_sec = 0;

  ret = mktime_utc (&etime);

  return ret;
}
