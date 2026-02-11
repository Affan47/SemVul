machtime (void)
{
  struct timeval tv;

  if (gettimeofday (&tv, NULL) < 0)
    {
      if (debug)
	fprintf (stderr, "Unable to get time of day\n");
      return 0L;
    }
#define OFFSET ((unsigned long)25567 * 24*60*60)
  return (htonl ((long) (tv.tv_sec + OFFSET)));
#undef OFFSET
}
