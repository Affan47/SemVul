target_filter (GdkXEvent *gdk_xevent,
               GdkEvent  *event,
               gpointer   data)
{
  XEvent *xevent = (XEvent *) gdk_xevent;

  switch (xevent->type)
    {
      case ButtonPress:
        handle_button_press_event (&xevent->xkey);
        clean_up ();
        return GDK_FILTER_REMOVE;
      case KeyPress:
        if (xevent->xkey.keycode == XKeysymToKeycode (xevent->xany.display, XK_Escape))
          {
            clean_up ();
            return GDK_FILTER_REMOVE;
          }
        break;
      default:
        break;
    }

  return GDK_FILTER_CONTINUE;
}
