disable_keyframes (const GValue *item, gpointer user_data)
{
  GstElement *element = g_value_get_object (item);
  GstElementFactory *factory;
  const gchar *factory_name;
  guint i;

  factory = gst_element_get_factory (element);
  if (!factory)
    return;

  factory_name = gst_plugin_feature_get_name (GST_PLUGIN_FEATURE (factory));
  if (!factory_name)
    return;

  for (i = 0; no_keyframe_property[i].element; i++)
    if (!strcmp (no_keyframe_property[i].element, factory_name))
      g_object_set (element, no_keyframe_property[i].property,
          no_keyframe_property[i].value, NULL);

}
