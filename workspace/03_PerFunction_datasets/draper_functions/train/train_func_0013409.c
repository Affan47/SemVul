cycle_timer (XtPointer closure, XtIntervalId *id)
{
  saver_info *si = (saver_info *) closure;
  saver_preferences *p = &si->prefs;
  Time how_long = p->cycle;

  if (si->selection_mode > 0 &&
      screenhack_running_p (si))


    how_long = 1000 * 60 * 60;

  if (si->dbox_up_p)
    {
      if (p->verbose_p)
	fprintf (stderr, "%s: dialog box up; delaying hack change.\n",
		 blurb());
      how_long = 30000;
    }
  else
    {
      int i;
      maybe_reload_init_file (si);
      for (i = 0; i < si->nscreens; i++)
        kill_screenhack (&si->screens[i]);

      raise_window (si, True, True, False);

      if (!si->throttled_p)
        for (i = 0; i < si->nscreens; i++)
          spawn_screenhack (&si->screens[i]);
      else
        {
          if (p->verbose_p)
            fprintf (stderr, "%s: not launching new hack (throttled.)\n",
                     blurb());
        }
    }

  if (how_long > 0)
    {
      si->cycle_id = XtAppAddTimeOut (si->app, how_long, cycle_timer,
                                      (XtPointer) si);

      if (p->debug_p)
        fprintf (stderr, "%s: starting cycle_timer (%ld, %ld)\n",
                 blurb(), how_long, si->cycle_id);
    }
  else
    {
      if (p->debug_p)
        fprintf (stderr, "%s: not starting cycle_timer: how_long == %ld\n",
                 blurb(), (unsigned long) how_long);
    }
}
