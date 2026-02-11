gst_rtsp_watch_send_message (GstRTSPWatch * watch, GstRTSPMessage * message,
    guint * id)
{
  GString *str;
  guint size;

  g_return_val_if_fail (watch != NULL, GST_RTSP_EINVAL);
  g_return_val_if_fail (message != NULL, GST_RTSP_EINVAL);


  str = message_to_string (watch->conn, message);
  size = str->len;
  return gst_rtsp_watch_write_data (watch,
      (guint8 *) g_string_free (str, FALSE), size, id);
}
