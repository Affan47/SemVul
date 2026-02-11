button_release_event_cb (ClutterActor *actor,
    ClutterButtonEvent *event,
    ChamplainMarker *marker)
{
  if ((event->type != CLUTTER_BUTTON_RELEASE) ||
      (event->button != 1))
    return FALSE;

  g_signal_handlers_disconnect_by_func (marker,
      button_release_event_cb,
      marker);

  g_signal_emit_by_name (marker, "button-release", event);

  return TRUE;
}
