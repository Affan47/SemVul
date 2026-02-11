window_configure_event_cb (GtkWidget *widget, GdkEventConfigure *event)
{
  if (!window_is_maximized && !window_is_fullscreen)
  {
    window_width = event->width;
    window_height = event->height;
  }

  return FALSE;
}
