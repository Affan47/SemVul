clutter_event_get (void)
{
  ClutterMainContext *context = _clutter_context_get_default ();

  if (context->events_queue == NULL)
    return NULL;

  if (g_queue_is_empty (context->events_queue))
    return NULL;

  return g_queue_pop_tail (context->events_queue);
}
