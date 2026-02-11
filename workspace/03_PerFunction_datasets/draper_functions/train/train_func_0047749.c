tvsum(struct timeval * p1, struct timeval * p2, struct timeval * p3)
{
  static char fnc[] = "tvsum";

  if ((p1->tv_sec < (long) (0)) && (p2->tv_sec < (long) (0))) {
    p3->tv_sec = (p1->tv_sec + 1);
    p3->tv_sec += (p2->tv_sec + 1);
    if (p3->tv_sec >= (long) (0)) {
      Warn("%t %s(): warning: negative overflow\n", fnc);
      p3->tv_sec = INT_MIN;
      p3->tv_usec = (long) (0);
      return 2;
    }
    p3->tv_usec = (p1->tv_usec - MILLION_USECS);
    p3->tv_usec += (p2->tv_usec - MILLION_USECS);
  } else if ((p1->tv_sec > (long) (0)) && (p2->tv_sec > (long) (0))) {
    p3->tv_sec = p1->tv_sec + p2->tv_sec;
    if (p3->tv_sec < (long) (0)) {

      Warn("%t %s(): warning: positive overflow\n", fnc);
      p3->tv_sec = INT_MAX;
      p3->tv_usec = MILLION_USECS - 1;
      return 1;
    }
    p3->tv_usec = p1->tv_usec + p2->tv_usec;
  } else {
    p3->tv_sec = p1->tv_sec + p2->tv_sec;
    p3->tv_usec = p1->tv_usec + p2->tv_usec;
  }
  return tvnorm(p3);
}
