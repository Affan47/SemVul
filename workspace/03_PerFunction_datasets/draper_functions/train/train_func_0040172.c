handle_motion_notify_event (GdkEventMotion *event)
{
  if (gtk_window != NULL && gtk_window_visible)
    {
      gdk_window_set_cursor (GDK_WINDOW (gtk_window->window), visible_cursor);
      cursor_timeout = 3;
    }
  return true;
}
