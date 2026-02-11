gst_auto_convert_get_or_make_element_from_factory (GstAutoConvert * autoconvert,
    GstElementFactory * factory)
{
  GstElement *element = NULL;
  GstElementFactory *loaded_factory =
      GST_ELEMENT_FACTORY (gst_plugin_feature_load (GST_PLUGIN_FEATURE
          (factory)));

  if (!loaded_factory)
    return NULL;

  element = gst_auto_convert_get_element_by_type (autoconvert,
      gst_element_factory_get_element_type (loaded_factory));

  if (!element) {
    element = gst_auto_convert_add_element (autoconvert, loaded_factory);
  }

  gst_object_unref (loaded_factory);

  return element;
}
