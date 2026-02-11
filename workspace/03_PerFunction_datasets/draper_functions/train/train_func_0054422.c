print_element_features (const gchar * element_name)
{
  GstPluginFeature *feature;


#if 0
  feature = gst_default_registry_find_feature (element_name,
      GST_TYPE_INDEX_FACTORY);
  if (feature) {
    n_print ("%s: an index\n", element_name);
    return 0;
  }
#endif
  feature = gst_registry_find_feature (gst_registry_get (), element_name,
      GST_TYPE_TYPE_FIND_FACTORY);
  if (feature) {
    n_print ("%s: a typefind function\n", element_name);
    return 0;
  }

  return -1;
}
