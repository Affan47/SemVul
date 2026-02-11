clutter_behaviour_rotate_new (ClutterAlpha           *alpha,
                              ClutterRotateAxis       axis,
                              ClutterRotateDirection  direction,
                              gdouble                 angle_start,
                              gdouble                 angle_end)
{
  g_return_val_if_fail (alpha == NULL || CLUTTER_IS_ALPHA (alpha), NULL);

  return g_object_new (CLUTTER_TYPE_BEHAVIOUR_ROTATE,
                       "alpha", alpha,
                       "axis", axis,
                       "direction", direction,
                       "angle-start", angle_start,
                       "angle-end", angle_end,
                       NULL);
}
