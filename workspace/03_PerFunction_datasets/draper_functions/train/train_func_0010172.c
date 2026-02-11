_clutter_process_event (ClutterEvent *event)
{
  ClutterMainContext *context;
  ClutterActor *stage;

  context = _clutter_context_get_default ();

  stage = CLUTTER_ACTOR (event->any.stage);
  if (stage == NULL)
    {
      CLUTTER_NOTE (EVENT, "Discarding event without a stage set");
      return;
    }


  context->current_event = g_slist_prepend (context->current_event, event);

  _clutter_process_event_details (stage, context, event);

  context->current_event = g_slist_delete_link (context->current_event, context->current_event);
}
