clutter_event_set_scroll_delta (ClutterEvent *event,
                                gdouble       dx,
                                gdouble       dy)
{
  g_return_if_fail (event != NULL);
  g_return_if_fail (event->type == CLUTTER_SCROLL);

  if (!is_event_allocated (event))
    return;

  event->scroll.direction = CLUTTER_SCROLL_SMOOTH;

  ((ClutterEventPrivate *) event)->delta_x = dx;
  ((ClutterEventPrivate *) event)->delta_y = dy;
}
