gst_controller_set_interpolation_mode (GstController * self,
    const gchar * property_name, GstInterpolateMode mode)
{
  gboolean res = FALSE;
  GstControlledProperty *prop;

  g_return_val_if_fail (GST_IS_CONTROLLER (self), FALSE);
  g_return_val_if_fail (property_name, FALSE);

  g_mutex_lock (self->lock);
  if ((prop = gst_controller_find_controlled_property (self, property_name))) {
    res = gst_controlled_property_set_interpolation_mode (prop, mode);
  }
  g_mutex_unlock (self->lock);

  return res;
}
