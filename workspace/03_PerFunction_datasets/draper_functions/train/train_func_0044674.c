enter (XCrossingEvent * e)
{
  Client *c;

  if (e->mode != NotifyGrab || e->detail != NotifyNonlinearVirtual)
    return;

  c = getclient (e->window, 0);

  if (c && c->parent && (c != current))
    {
      XMapRaised (dpy, c->parent);
      active (c);
    }
  else
    {
      XSetInputFocus (dpy, e->window, RevertToPointerRoot, e->time);
    }
}
