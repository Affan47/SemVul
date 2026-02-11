gst_rtsp_message_new_data (GstRTSPMessage ** msg, guint8 channel)
{
  GstRTSPMessage *newmsg;

  g_return_val_if_fail (msg != NULL, GST_RTSP_EINVAL);

  newmsg = g_new0 (GstRTSPMessage, 1);

  *msg = newmsg;

  return gst_rtsp_message_init_data (newmsg, channel);
}
