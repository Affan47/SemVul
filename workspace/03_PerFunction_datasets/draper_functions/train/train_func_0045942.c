start_timer(int n)
{
  gg_assert(n >= 0 && n < NUMBER_OF_TIMERS);
  if (!showtime)
    return;

  timers[n] = gg_cputime();
}
