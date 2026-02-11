fwritable (o)
     int o;
{
#if HAVE_SELECT

  int iwrite;
  struct timeval stime;
  int cfds;

  iwrite = 1 << o;

  stime.tv_sec = 0;
  stime.tv_usec = 0;

  cfds = select (o + 1, (pointer) NULL, (pointer) &iwrite,
		 (pointer) NULL, &stime);
  if (cfds < 0)
    {
      perror ("select");
      uchild (SIGCHLD);
    }

  return cfds > 0;

#else

#if HAVE_POLL

  struct pollfd s;
  int cfds;

  s.fd = o;
  s.events = POLLOUT;

  cfds = poll (&s, 1, 0);
  if (cfds < 0)
    {
      perror ("poll");
      uchild (SIGCHLD);
    }

  return cfds > 0;

#endif
#endif
}
