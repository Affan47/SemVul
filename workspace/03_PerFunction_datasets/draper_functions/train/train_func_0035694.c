plugin_init (GstPlugin * plugin)
{
  GST_DEBUG_CATEGORY_INIT (equalizer_debug, "equalizer", 0, "equalizer");

  if (!(gst_element_register (plugin, "equalizer-nbands", GST_RANK_NONE,
              GST_TYPE_IIR_EQUALIZER_NBANDS)))
    return FALSE;

  if (!(gst_element_register (plugin, "equalizer-3bands", GST_RANK_NONE,
              GST_TYPE_IIR_EQUALIZER_3BANDS)))
    return FALSE;

  if (!(gst_element_register (plugin, "equalizer-10bands", GST_RANK_NONE,
              GST_TYPE_IIR_EQUALIZER_10BANDS)))
    return FALSE;

  return TRUE;
}
