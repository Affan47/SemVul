plugin_init (GstPlugin * plugin)
{
#ifdef G_OS_WIN32
  if (!gst_udp_net_utils_win32_wsa_startup (GST_OBJECT (plugin)))
    return FALSE;
#endif


  gst_netbuffer_get_type ();

  if (!gst_element_register (plugin, "udpsink", GST_RANK_NONE,
          GST_TYPE_UDPSINK))
    return FALSE;

  if (!gst_element_register (plugin, "multiudpsink", GST_RANK_NONE,
          GST_TYPE_MULTIUDPSINK))
    return FALSE;

  if (!gst_element_register (plugin, "dynudpsink", GST_RANK_NONE,
          GST_TYPE_DYNUDPSINK))
    return FALSE;

  if (!gst_element_register (plugin, "udpsrc", GST_RANK_NONE, GST_TYPE_UDPSRC))
    return FALSE;

  return TRUE;
}
