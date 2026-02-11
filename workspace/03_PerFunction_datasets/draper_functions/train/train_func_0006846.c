getTime(void)
{

#if defined(_POSIX_TIMERS) && defined(_POSIX_MONOTONIC_CLOCK)
  struct timespec tp;
  if (clock_gettime(CLOCK_MONOTONIC, &tp) == 0)
    return tp.tv_nsec / 1000000 + (tp.tv_sec % 1000000)*1000;

#endif
#if !defined(WIN32)
  struct timeval tv;
  if (gettimeofday(&tv,NULL) == 0)
    return tv.tv_usec/1000 + (tv.tv_sec % 1000000)*1000;
  else
    return 0;
#elif defined(WIN32)
  return timeGetTime();
#endif
}
