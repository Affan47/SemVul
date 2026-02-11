gst_base_parse_frame_free (GstBaseParseFrame * frame)
{
  GST_TRACE ("freeing frame %p", frame);

  if (frame->buffer) {
    gst_buffer_unref (frame->buffer);
    frame->buffer = NULL;
  }

  if (!(frame->_private_flags & GST_BASE_PARSE_FRAME_PRIVATE_FLAG_NOALLOC)) {
    g_slice_free (GstBaseParseFrame, frame);
  } else {
    memset (frame, 0, sizeof (*frame));
  }
}
