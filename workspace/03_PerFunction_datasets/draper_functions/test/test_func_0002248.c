gst_controller_set_from_list (GstController * self, const gchar * property_name,
    GSList * timedvalues)
{
  gboolean res = FALSE;
  GstControlledProperty *prop;

  g_return_val_if_fail (GST_IS_CONTROLLER (self), FALSE);
  g_return_val_if_fail (property_name, FALSE);

  g_mutex_lock (self->lock);
  if ((prop = gst_controller_find_controlled_property (self, property_name))) {

    if (!prop->csource)
      gst_controlled_property_add_interpolation_control_source (prop);

    if (!GST_IS_INTERPOLATION_CONTROL_SOURCE (prop->csource))
      goto out;

    res =
        gst_interpolation_control_source_set_from_list
        (GST_INTERPOLATION_CONTROL_SOURCE (prop->csource), timedvalues);
  }

out:
  g_mutex_unlock (self->lock);

  return res;
}
