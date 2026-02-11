gst_rtsp_message_set_body (GstRTSPMessage * msg, const guint8 * data,
    guint size)
{
  g_return_val_if_fail (msg != NULL, GST_RTSP_EINVAL);

  return gst_rtsp_message_take_body (msg, g_memdup (data, size), size);
}
