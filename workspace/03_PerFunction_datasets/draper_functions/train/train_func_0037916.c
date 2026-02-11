ev_timer_again (EV_P_ ev_timer *w)
{
  EV_FREQUENT_CHECK;

  if (ev_is_active (w))
    {
      if (w->repeat)
        {
          ev_at (w) = mn_now + w->repeat;
          ANHE_at_cache (timers [ev_active (w)]);
          adjustheap (timers, timercnt, ev_active (w));
        }
      else
        ev_timer_stop (EV_A_ w);
    }
  else if (w->repeat)
    {
      ev_at (w) = w->repeat;
      ev_timer_start (EV_A_ w);
    }

  EV_FREQUENT_CHECK;
}
