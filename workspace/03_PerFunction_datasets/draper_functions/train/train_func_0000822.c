gst_rtsp_message_init (GstRTSPMessage * msg)
{
  g_return_val_if_fail (msg != NULL, GST_RTSP_EINVAL);

  gst_rtsp_message_unset (msg);

  msg->type = GST_RTSP_MESSAGE_INVALID;
  msg->hdr_fields = g_array_new (FALSE, FALSE, sizeof (RTSPKeyValue));

  return GST_RTSP_OK;
}
