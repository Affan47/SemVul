ev_child_start (EV_P_ ev_child *w)
{
#if EV_MULTIPLICITY
  assert (("libev: child watchers are only supported in the default loop", loop == ev_default_loop_ptr));
#endif
  if (expect_false (ev_is_active (w)))
    return;

  EV_FREQUENT_CHECK;

  ev_start (EV_A_ (W)w, 1);
  wlist_add (&childs [w->pid & (EV_PID_HASHSIZE - 1)], (WL)w);

  EV_FREQUENT_CHECK;
}
