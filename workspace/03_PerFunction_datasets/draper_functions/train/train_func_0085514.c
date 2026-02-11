gst_h264_parse_wrap_nal (GstH264Parse * h264parse, guint format, guint8 * data,
    guint size)
{
  GstBuffer *buf;
  guint nl = h264parse->nal_length_size;
  guint32 tmp;

  GST_DEBUG_OBJECT (h264parse, "nal length %d", size);

  buf = gst_buffer_new_allocate (NULL, 4 + size, NULL);
  if (format == GST_H264_PARSE_FORMAT_AVC
      || format == GST_H264_PARSE_FORMAT_AVC3) {
    tmp = GUINT32_TO_BE (size << (32 - 8 * nl));
  } else {


    nl = 4;
    tmp = GUINT32_TO_BE (1);
  }

  gst_buffer_fill (buf, 0, &tmp, sizeof (guint32));
  gst_buffer_fill (buf, nl, data, size);
  gst_buffer_set_size (buf, size + nl);

  return buf;
}
