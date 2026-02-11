gst_aiff_mux_push_header (GstAiffMux * aiffmux, guint32 audio_data_size)
{
  GstFlowReturn ret;
  GstBuffer *outbuf;
  GstByteWriter *writer;
  GstSegment seg;


  gst_segment_init (&seg, GST_FORMAT_BYTES);

  if (gst_pad_push_event (aiffmux->srcpad,
          gst_event_new_segment (&seg)) == FALSE) {
    GST_ELEMENT_WARNING (aiffmux, STREAM, MUX,
        ("An output stream seeking error occurred when multiplexing."),
        ("Failed to seek to beginning of stream to write header."));
  }

  GST_DEBUG_OBJECT (aiffmux, "writing header with datasize=%u",
      audio_data_size);

  writer = gst_byte_writer_new_with_size (AIFF_HEADER_LEN, TRUE);

  gst_aiff_mux_write_form_header (aiffmux, audio_data_size, writer);
  gst_aiff_mux_write_comm_header (aiffmux, audio_data_size, writer);
  gst_aiff_mux_write_ssnd_header (aiffmux, audio_data_size, writer);

  outbuf = gst_byte_writer_free_and_get_buffer (writer);

  ret = gst_pad_push (aiffmux->srcpad, outbuf);

  if (ret != GST_FLOW_OK) {
    GST_WARNING_OBJECT (aiffmux, "push header failed: flow = %s",
        gst_flow_get_name (ret));
  }

  return ret;
}
