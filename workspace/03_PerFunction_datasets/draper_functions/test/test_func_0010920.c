on_crossing (ClutterActor *actor,
             ClutterEvent *event)
{
  gboolean is_enter = clutter_event_type (event) == CLUTTER_ENTER;
  float zpos;

  if (is_enter)
    zpos = -250.0;
  else
    zpos = 0.0;

  clutter_actor_save_easing_state (actor);
  clutter_actor_set_easing_duration (actor, 500);
  clutter_actor_set_easing_mode (actor, CLUTTER_EASE_OUT_BOUNCE);
  clutter_actor_set_z_position (actor, zpos);
  clutter_actor_restore_easing_state (actor);

  return CLUTTER_EVENT_STOP;
}
