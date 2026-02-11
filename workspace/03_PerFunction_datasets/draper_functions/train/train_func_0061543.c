gst_controller_set_disabled (GstController * self, gboolean disabled)
{
  GList *node;
  GstControlledProperty *prop;

  g_return_if_fail (GST_IS_CONTROLLER (self));

  g_mutex_lock (self->lock);
  for (node = self->properties; node; node = node->next) {
    prop = node->data;
    prop->disabled = disabled;
  }
  g_mutex_unlock (self->lock);
}
