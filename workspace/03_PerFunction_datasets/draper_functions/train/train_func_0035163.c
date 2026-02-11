gst_ximagesink_set_event_handling (GstVideoOverlay * overlay,
    gboolean handle_events)
{
  GstXImageSink *ximagesink = GST_XIMAGESINK (overlay);

  ximagesink->handle_events = handle_events;

  g_mutex_lock (&ximagesink->flow_lock);

  if (G_UNLIKELY (!ximagesink->xwindow)) {
    g_mutex_unlock (&ximagesink->flow_lock);
    return;
  }

  g_mutex_lock (&ximagesink->x_lock);

  if (handle_events) {
    if (ximagesink->xwindow->internal) {
      XSelectInput (ximagesink->xcontext->disp, ximagesink->xwindow->win,
          ExposureMask | StructureNotifyMask | PointerMotionMask |
          KeyPressMask | KeyReleaseMask | ButtonPressMask | ButtonReleaseMask);
    } else {
      XSelectInput (ximagesink->xcontext->disp, ximagesink->xwindow->win,
          ExposureMask | StructureNotifyMask | PointerMotionMask |
          KeyPressMask | KeyReleaseMask);
    }
  } else {
    XSelectInput (ximagesink->xcontext->disp, ximagesink->xwindow->win, 0);
  }

  g_mutex_unlock (&ximagesink->x_lock);

  g_mutex_unlock (&ximagesink->flow_lock);
}
