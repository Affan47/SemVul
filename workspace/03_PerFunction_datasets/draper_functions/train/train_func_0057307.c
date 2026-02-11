plugin_init (GstPlugin * plugin)
{
  if (!gst_element_register (plugin, "gsettingsaudiosink", GST_RANK_NONE,
          GST_TYPE_GSETTINGS_AUDIO_SINK) ||
      !gst_element_register (plugin, "gsettingsaudiosrc", GST_RANK_NONE,
          GST_TYPE_GSETTINGS_AUDIO_SRC) ||
      !gst_element_register (plugin, "gsettingsvideosink", GST_RANK_NONE,
          GST_TYPE_GSETTINGS_VIDEO_SINK) ||
      !gst_element_register (plugin, "gsettingsvideosrc", GST_RANK_NONE,
          GST_TYPE_GSETTINGS_VIDEO_SRC))
    return FALSE;

  return TRUE;
}
