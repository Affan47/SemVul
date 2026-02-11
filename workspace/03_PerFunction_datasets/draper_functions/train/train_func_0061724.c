prev_screen (ScreenInfo * s)
{
  ScreenInfo *ns;
  int cur;

  if (!s)
    abort ();

  cur = s->num;

  if (--cur < 0)
    cur = num_screens - 1;

  raise_tbar (s);

  ns = &screens[cur];

  setmouse (DisplayWidth (dpy, cur) / 2, DisplayHeight (dpy, cur) - 2, ns);

  if (!ns->notile_raised[ns->desktop] && ns->focused[ns->desktop])
    active (ns->focused[ns->desktop]);
  else if (ns->notile_raised[ns->desktop] && ns->notilefocused[ns->desktop])
    active (ns->notilefocused[ns->desktop]);
  else
    {
      revert_same (ns);

      if (!current)
	revert_window (ns);
    }
}
