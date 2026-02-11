gst_rtp_buffer_list_get_ssrc (GstBufferList * list)
{
  GstBuffer *buffer;

  buffer = gst_buffer_list_get (list, 0, 0);
  g_return_val_if_fail (buffer != NULL, 0);

  return g_ntohl (GST_RTP_HEADER_SSRC (GST_BUFFER_DATA (buffer)));
}
