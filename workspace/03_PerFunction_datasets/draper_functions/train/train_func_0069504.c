capture_release_event_cb (ClutterActor *stage,
    ClutterButtonEvent *event,
    ChamplainMarker *marker)
{
  ChamplainMarkerPrivate *priv = marker->priv;

  if ((event->type != CLUTTER_BUTTON_RELEASE) ||
      (event->button != 1))
    return FALSE;

  g_signal_handlers_disconnect_by_func (stage,
      motion_event_cb,
      marker);
  g_signal_handlers_disconnect_by_func (stage,
      capture_release_event_cb,
      marker);

  if (priv->moved)
    g_signal_emit_by_name (marker, "drag-finish", event);
  else
    g_signal_emit_by_name (marker, "button-release", event);

  return TRUE;
}
