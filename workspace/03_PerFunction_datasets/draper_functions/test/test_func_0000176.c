ev_feed_signal_event (EV_P_ int signum)
{
  WL w;

  if (expect_false (signum <= 0 || signum > EV_NSIG))
    return;

  --signum;

#if EV_MULTIPLICITY


  if (expect_false (signals [signum].loop != EV_A))
    return;
#endif

  signals [signum].pending = 0;

  for (w = signals [signum].head; w; w = w->next)
    ev_feed_event (EV_A_ (W)w, EV_SIGNAL);
}
