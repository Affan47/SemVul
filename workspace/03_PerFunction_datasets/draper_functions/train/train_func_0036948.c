clutter_event_set_source_device (ClutterEvent       *event,
                                 ClutterInputDevice *device)
{
  ClutterEventPrivate *real_event;

  g_return_if_fail (event != NULL);
  g_return_if_fail (device == NULL || CLUTTER_IS_INPUT_DEVICE (device));

  if (!is_event_allocated (event))
    return;

  real_event = (ClutterEventPrivate *) event;
  real_event->source_device = device;
}
