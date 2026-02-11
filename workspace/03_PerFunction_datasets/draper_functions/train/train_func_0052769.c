start_notice_events_timer (saver_info *si, Window w, Bool verbose_p)
{
  saver_preferences *p = &si->prefs;
  struct notice_events_timer_arg *arg =
    (struct notice_events_timer_arg *) malloc(sizeof(*arg));
  arg->si = si;
  arg->w = w;
  XtAppAddTimeOut (si->app, p->notice_events_timeout, notice_events_timer,
		   (XtPointer) arg);

  if (verbose_p)
    fprintf (stderr, "%s: starting notice_events_timer for 0x%X (%lu)\n",
             blurb(), (unsigned int) w, p->notice_events_timeout);
}
