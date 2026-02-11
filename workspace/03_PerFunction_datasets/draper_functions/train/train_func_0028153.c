ev_child_stop (EV_P_ ev_child *w)
{
  clear_pending (EV_A_ (W)w);
  if (expect_false (!ev_is_active (w)))
    return;

  EV_FREQUENT_CHECK;

  wlist_del (&childs [w->pid & (EV_PID_HASHSIZE - 1)], (WL)w);
  ev_stop (EV_A_ (W)w);

  EV_FREQUENT_CHECK;
}
