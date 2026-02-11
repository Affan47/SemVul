gst_plugin_feature_get_plugin_name (GstPluginFeature * feature)
{
  g_return_val_if_fail (GST_IS_PLUGIN_FEATURE (feature), NULL);

  if (feature->plugin == NULL)
    return NULL;

  return gst_plugin_get_name (feature->plugin);
}
