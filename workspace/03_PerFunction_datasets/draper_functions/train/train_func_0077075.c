ev_idle_stop (EV_P_ ev_idle *w) EV_THROW
{
  clear_pending (EV_A_ (W)w);
  if (expect_false (!ev_is_active (w)))
    return;

  EV_FREQUENT_CHECK;

  {
    int active = ev_active (w);

    idles [ABSPRI (w)][active - 1] = idles [ABSPRI (w)][--idlecnt [ABSPRI (w)]];
    ev_active (idles [ABSPRI (w)][active - 1]) = active;

    ev_stop (EV_A_ (W)w);
    --idleall;
  }

  EV_FREQUENT_CHECK;
}
