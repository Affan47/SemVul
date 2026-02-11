ev_stat_stop (EV_P_ ev_stat *w) EV_THROW
{
  clear_pending (EV_A_ (W)w);
  if (expect_false (!ev_is_active (w)))
    return;

  EV_FREQUENT_CHECK;

#if EV_USE_INOTIFY
  infy_del (EV_A_ w);
#endif

  if (ev_is_active (&w->timer))
    {
      ev_ref (EV_A);
      ev_timer_stop (EV_A_ &w->timer);
    }

  ev_stop (EV_A_ (W)w);

  EV_FREQUENT_CHECK;
}
