events_queue (ClutterBackendX11 *backend_x11)
{
  ClutterBackend *backend = CLUTTER_BACKEND (backend_x11);
  Display *xdisplay = backend_x11->xdpy;
  ClutterEvent *event;
  XEvent xevent;

  while (!clutter_events_pending () && XPending (xdisplay))
    {
      XNextEvent (xdisplay, &xevent);

      event = clutter_event_new (CLUTTER_NOTHING);

#ifdef HAVE_XGE
      XGetEventData (xdisplay, &xevent.xcookie);
#endif

      if (_clutter_backend_translate_event (backend, &xevent, event))
        _clutter_event_push (event, FALSE);
      else
        clutter_event_free (event);

#ifdef HAVE_XGE
      XFreeEventData (xdisplay, &xevent.xcookie);
#endif
    }
}
