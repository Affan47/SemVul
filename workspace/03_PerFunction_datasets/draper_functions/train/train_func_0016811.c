totem_aspect_frame_set_rotation_internal (TotemAspectFrame *frame,
					  gdouble           rotation,
					  gboolean          animate)
{
  TotemAspectFramePrivate *priv = frame->priv;
  ClutterActor *actor;
  gfloat frame_width, frame_height;
  gfloat child_width, child_height;
  gfloat child_dest_width, child_dest_height;
  gdouble frame_aspect;
  gdouble child_aspect;

  actor = clutter_actor_get_child_at_index (CLUTTER_ACTOR (frame), 0);
  if (!actor)
    return;

  totem_aspect_frame_get_size (frame, rotation,
                               &frame_width, &frame_height);
  _get_allocation (actor, &child_width, &child_height);

  if (child_width <= 0.0f || child_height <= 0.0f)
    return;

  frame_aspect = frame_width / frame_height;
  child_aspect = child_width / child_height;

  if ((frame_aspect < child_aspect) ^ priv->expand)
    {
      child_dest_width = frame_width;
      child_dest_height = frame_width / child_aspect;
    }
  else
    {
      child_dest_height = frame_height;
      child_dest_width = frame_height * child_aspect;
    }

  clutter_actor_set_pivot_point (actor, 0.5, 0.5);

  if (animate)
    {
      clutter_actor_save_easing_state (actor);
      clutter_actor_set_easing_duration (actor, 500);
    }

  clutter_actor_set_rotation_angle (actor, CLUTTER_Z_AXIS, rotation);
  clutter_actor_set_scale (actor,
                           child_dest_width / child_width,
                           child_dest_height / child_height);

  if (animate)
    clutter_actor_restore_easing_state (actor);
}
