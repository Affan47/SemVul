_glade_design_layout_coords_from_event (GdkWindow *parent,
                                        GdkEvent *event,
                                        gint *x, gint *y)
{
  GdkWindow *child = event->any.window;
  gdouble xx, yy;

  if (!gdk_event_get_coords (event, &xx, &yy))
    {
      *x = *y = 0;
      g_warning ("wrong event type %d", event->type);
      return;
    }

  while (child && parent != child)
    {
      gdk_window_coords_to_parent (child, xx, yy, &xx, &yy);
      child = gdk_window_get_parent (child);
    }

  *x = xx;
  *y = yy;
}
