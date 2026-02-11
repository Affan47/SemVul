element_filter (GstPluginFeature * feature, FilterData * data)
{
  gboolean res;


  if (G_UNLIKELY (!GST_IS_ELEMENT_FACTORY (feature)))
    return FALSE;

  res = (gst_plugin_feature_get_rank (feature) >= data->minrank) &&
      gst_element_factory_list_is_type (GST_ELEMENT_FACTORY_CAST (feature),
      data->type);

  return res;
}
