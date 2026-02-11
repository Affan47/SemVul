mx_window_set_window_rotation (MxWindow         *window,
                               MxWindowRotation  rotation)
{
  guint msecs;
  MxWindowPrivate *priv;

  g_return_if_fail (MX_IS_WINDOW (window));

  priv = window->priv;
  if (priv->rotation == rotation)
    return;

  if (((priv->rotation == MX_WINDOW_ROTATION_0) ||
       (priv->rotation == MX_WINDOW_ROTATION_180)) &&
      ((rotation == MX_WINDOW_ROTATION_90) ||
       (rotation == MX_WINDOW_ROTATION_270)))
    priv->rotate_size = TRUE;
  else if (((priv->rotation == MX_WINDOW_ROTATION_90) ||
            (priv->rotation == MX_WINDOW_ROTATION_270)) &&
           ((rotation == MX_WINDOW_ROTATION_0) ||
            (rotation == MX_WINDOW_ROTATION_180)))
    priv->rotate_size = TRUE;

  priv->rotation = rotation;

  priv->start_angle = priv->angle;
  switch (rotation)
    {
    case MX_WINDOW_ROTATION_0 :
      priv->end_angle = 0.f;
      break;
    case MX_WINDOW_ROTATION_90 :
      priv->end_angle = 90.f;
      break;
    case MX_WINDOW_ROTATION_180 :
      priv->end_angle = 180.f;
      break;
    case MX_WINDOW_ROTATION_270 :
      priv->end_angle = 270.f;
      break;
    }

  if (priv->end_angle - priv->start_angle > 180.f)
    priv->end_angle -= 360.f;
  else if (priv->end_angle - priv->start_angle < -180.f)
    priv->end_angle += 360.f;

  msecs = (guint)((ABS (priv->end_angle - priv->start_angle) / 90.f) * 400.f);
  clutter_timeline_rewind (priv->rotation_timeline);
  clutter_timeline_set_duration (priv->rotation_timeline, msecs);
  clutter_timeline_start (priv->rotation_timeline);

  g_object_notify (G_OBJECT (window), "window-rotation");
}
