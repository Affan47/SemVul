gst_controller_get_control_source (GstController * self,
    const gchar * property_name)
{
  GstControlledProperty *prop;
  GstControlSource *ret = NULL;

  g_return_val_if_fail (GST_IS_CONTROLLER (self), NULL);
  g_return_val_if_fail (property_name, NULL);

  g_mutex_lock (self->lock);
  if ((prop = gst_controller_find_controlled_property (self, property_name))) {
    ret = prop->csource;
  }
  g_mutex_unlock (self->lock);

  if (ret)
    g_object_ref (ret);

  return ret;
}
