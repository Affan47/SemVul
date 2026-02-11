periodics_reschedule (EV_P)
{
  int i;


  for (i = HEAP0; i < periodiccnt + HEAP0; ++i)
    {
      ev_periodic *w = (ev_periodic *)ANHE_w (periodics [i]);

      if (w->reschedule_cb)
        ev_at (w) = w->reschedule_cb (w, ev_rt_now);
      else if (w->interval)
        ev_at (w) = w->offset + ceil ((ev_rt_now - w->offset) / w->interval) * w->interval;

      ANHE_at_cache (periodics [i]);
    }

  reheap (periodics, periodiccnt);
}
