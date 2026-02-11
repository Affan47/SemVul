clutter_pan_action_set_pan_axis (ClutterPanAction *self,
                                 ClutterPanAxis    axis)
{
  ClutterPanActionPrivate *priv;

  g_return_if_fail (CLUTTER_IS_PAN_ACTION (self));
  g_return_if_fail (axis >= CLUTTER_PAN_AXIS_NONE &&
                    axis <= CLUTTER_PAN_Y_AXIS);

  priv = self->priv;

  if (priv->pan_axis == axis)
    return;

  priv->pan_axis = axis;

  g_object_notify_by_pspec (G_OBJECT (self), pan_props[PROP_PAN_AXIS]);
}
