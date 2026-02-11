clutter_pan_action_real_pan (ClutterPanAction *self,
                             ClutterActor     *actor,
                             gboolean          is_interpolated)
{
  ClutterPanActionPrivate *priv = self->priv;
  gfloat dx, dy;
  ClutterMatrix transform;

  clutter_pan_action_get_motion_delta (self, 0, &dx, &dy);

  switch (priv->pan_axis)
    {
    case CLUTTER_PAN_AXIS_NONE:
      break;

    case CLUTTER_PAN_X_AXIS:
      dy = 0.0f;
      break;

    case CLUTTER_PAN_Y_AXIS:
      dx = 0.0f;
      break;
    }

  clutter_actor_get_child_transform (actor, &transform);
  cogl_matrix_translate (&transform, dx, dy, 0.0f);
  clutter_actor_set_child_transform (actor, &transform);
  return TRUE;
}
