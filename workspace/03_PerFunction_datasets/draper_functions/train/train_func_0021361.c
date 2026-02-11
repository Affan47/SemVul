plugin_init (GstPlugin * plugin)
{
  gst_controller_init (NULL, NULL);

  return (gst_element_register (plugin, "gamma", GST_RANK_NONE, GST_TYPE_GAMMA)
      && gst_element_register (plugin, "videobalance", GST_RANK_NONE,
          GST_TYPE_VIDEO_BALANCE)
      && gst_element_register (plugin, "videoflip", GST_RANK_NONE,
          GST_TYPE_VIDEO_FLIP));
}
