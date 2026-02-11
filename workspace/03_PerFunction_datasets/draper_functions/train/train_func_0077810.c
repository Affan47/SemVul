xanalogtv_event (Display *dpy, Window window, void *closure, XEvent *event)
{
  struct state *st = (struct state *) closure;

  if (event->type == ButtonPress)
    {
      st->change_now = 1;
      return True;
    }
  else if (event->type == KeyPress)
    {
      KeySym keysym;
      char c = 0;
      XLookupString (&event->xkey, &c, 1, &keysym, 0);
      if (c == ' ' || c == '\t' || c == '\r' || c == '\n')
        {
          st->change_now = 1;
          return True;
        }
    }

  return False;
}
