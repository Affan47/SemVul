militime(char* sec, char* usec)
{
  struct timeval tv;
  static char timebuf[18];

  gettimeofday(&tv, NULL);
  if (sec && usec)
    sprintf(timebuf, "%ld",
        (tv.tv_sec - atoi(sec)) * 1000 + (tv.tv_usec - atoi(usec)) / 1000);
  else
    sprintf(timebuf, "%ld %ld", tv.tv_sec, tv.tv_usec);
  return timebuf;
}
