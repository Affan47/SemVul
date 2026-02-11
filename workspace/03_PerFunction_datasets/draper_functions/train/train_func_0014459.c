gst_ogg_avi_parse_push_packet (GstOggAviParse * ogg, ogg_packet * packet)
{
  GstBuffer *buffer;
  GstFlowReturn result;


  buffer = gst_buffer_new_and_alloc (packet->bytes);
  gst_buffer_fill (buffer, 0, packet->packet, packet->bytes);

  GST_LOG_OBJECT (ogg, "created buffer %p from page", buffer);

  GST_BUFFER_OFFSET_END (buffer) = packet->granulepos;

  if (ogg->discont) {
    GST_BUFFER_FLAG_SET (buffer, GST_BUFFER_FLAG_DISCONT);
    ogg->discont = FALSE;
  }

  result = gst_pad_push (ogg->srcpad, buffer);

  return result;
}
