ev_fork_start (EV_P_ ev_fork *w)
{
  if (expect_false (ev_is_active (w)))
    return;

  EV_FREQUENT_CHECK;

  ev_start (EV_A_ (W)w, ++forkcnt);
  array_needsize (ev_fork *, forks, forkmax, forkcnt, EMPTY2);
  forks [forkcnt - 1] = w;

  EV_FREQUENT_CHECK;
}
