mx_draggable_real_enable (MxDraggable *draggable)
{
  DragContext *context;
  ClutterActor *stage;

  context = g_object_get_qdata (G_OBJECT (draggable), quark_draggable_context);
  if (G_UNLIKELY (context != NULL))
    return;

  stage = clutter_actor_get_stage (CLUTTER_ACTOR (draggable));
  if (G_UNLIKELY (stage == NULL))
    {
      g_warning ("Draggable actors can only be enabled when they "
                 "on the stage");
      return;
    }

  context = drag_context_create (draggable);
  g_signal_connect (draggable,
                    "button-press-event", G_CALLBACK (on_draggable_press),
                    context);

  g_object_notify (G_OBJECT (draggable), "drag-enabled");
}
