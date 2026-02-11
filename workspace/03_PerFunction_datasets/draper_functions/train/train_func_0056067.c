gst_ebml_read_buffer (GstEbmlRead * ebml, guint32 * id, GstBuffer ** buf)
{
  guint64 length;
  guint prefix;
  GstFlowReturn ret;

  ret = gst_ebml_peek_id_full (ebml, id, &length, &prefix);
  if (ret != GST_FLOW_OK)
    return ret;


  if (!gst_byte_reader_skip (gst_ebml_read_br (ebml), prefix))
    return GST_FLOW_ERROR;

  if (G_LIKELY (length > 0)) {
    guint offset;

    offset = gst_ebml_read_get_pos (ebml) - ebml->offset;
    if (G_LIKELY (gst_byte_reader_skip (gst_ebml_read_br (ebml), length))) {
      *buf = gst_buffer_copy_region (ebml->buf, GST_BUFFER_COPY_ALL,
          offset, length);
    } else {
      *buf = NULL;
      return GST_FLOW_PARSE;
    }
  } else {
    *buf = gst_buffer_new ();
  }

  return ret;
}
