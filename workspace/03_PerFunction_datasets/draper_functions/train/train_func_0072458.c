gst_base_parse_frame_new (GstBuffer * buffer, GstBaseParseFrameFlags flags,
    gint overhead)
{
  GstBaseParseFrame *frame;

  frame = g_slice_new0 (GstBaseParseFrame);
  frame->buffer = gst_buffer_ref (buffer);

  GST_TRACE ("created frame %p", frame);
  return frame;
}
