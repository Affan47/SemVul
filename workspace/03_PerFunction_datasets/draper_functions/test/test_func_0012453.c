plugin_init (GstPlugin * plugin)
{
  GST_DEBUG_CATEGORY_INIT (gst_jp2k_decimator_debug, "jp2kdecimator", 0,
      "JPEG2000 decimator");

  gst_element_register (plugin, "jp2kdecimator", GST_RANK_NONE,
      gst_jp2k_decimator_get_type ());

  return TRUE;
}
