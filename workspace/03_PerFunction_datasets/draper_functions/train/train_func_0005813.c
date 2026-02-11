champlain_marker_animate_in_with_delay (ChamplainMarker *marker,
    guint delay)
{
  gfloat y;

  g_return_if_fail (CHAMPLAIN_IS_MARKER (marker));

  clutter_actor_show (CLUTTER_ACTOR (marker));
  clutter_actor_set_opacity (CLUTTER_ACTOR (marker), 0);
  clutter_actor_set_scale (CLUTTER_ACTOR (marker), 1.5, 1.5);
  clutter_actor_get_position (CLUTTER_ACTOR (marker), NULL, &y);
  clutter_actor_move_by (CLUTTER_ACTOR (marker), 0, -100);

  clutter_actor_save_easing_state (CLUTTER_ACTOR (marker));
  clutter_actor_set_easing_delay (CLUTTER_ACTOR (marker), delay);
  clutter_actor_set_easing_mode (CLUTTER_ACTOR (marker), CLUTTER_EASE_OUT_BOUNCE);
  clutter_actor_set_easing_duration (CLUTTER_ACTOR (marker), 1000);
  clutter_actor_set_opacity (CLUTTER_ACTOR (marker), 255);
  clutter_actor_set_scale (CLUTTER_ACTOR (marker), 1.0, 1.0);
  clutter_actor_set_y (CLUTTER_ACTOR (marker), y);
  clutter_actor_restore_easing_state (CLUTTER_ACTOR (marker));
}
