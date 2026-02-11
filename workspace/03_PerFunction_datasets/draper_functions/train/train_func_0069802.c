discard_events(long event_type, Window w, XEvent *last_ev)
{
  XEvent e;

  XSync(dpy, 0);
  while (FCheckTypedWindowEvent(dpy, w, event_type, &e))
  {

    if (last_ev)
    {
      memcpy(last_ev, &e, sizeof(XEvent));
    }
  }

  return;
}
