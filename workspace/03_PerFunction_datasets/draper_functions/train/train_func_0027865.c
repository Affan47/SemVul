event_base_loopexit (struct event_base *base, struct timeval *tv)
{
  ev_tstamp after = ev_tv_get (tv);
  dLOOPbase;

  ev_once (EV_A_ -1, 0, after >= 0. ? after : 0., ev_x_loopexit_cb, (void *)base);

  return 0;
}
