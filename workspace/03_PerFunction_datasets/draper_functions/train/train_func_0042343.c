gst_dirac_parse_check_valid_frame (GstBaseParse * parse,
    GstBaseParseFrame * frame, guint * framesize, gint * skipsize)
{
  GstByteReader reader = GST_BYTE_READER_INIT_FROM_BUFFER (frame->buffer);
  int off;
  guint32 next_header;
  guint8 *data;
  int size;
  gboolean have_picture = FALSE;
  int offset;

  data = GST_BUFFER_DATA (frame->buffer);
  size = GST_BUFFER_SIZE (frame->buffer);

  if (G_UNLIKELY (size < 13))
    return FALSE;

  GST_DEBUG ("%d: %02x %02x %02x %02x", size, data[0], data[1], data[2],
      data[3]);

  if (GST_READ_UINT32_BE (data) != 0x42424344) {
    off = gst_byte_reader_masked_scan_uint32 (&reader, 0xffffffff,
        0x42424344, 0, GST_BUFFER_SIZE (frame->buffer));

    if (off < 0) {
      *skipsize = GST_BUFFER_SIZE (frame->buffer) - 3;
      return FALSE;
    }

    GST_LOG_OBJECT (parse, "possible sync at buffer offset %d", off);

    GST_DEBUG ("skipping %d", off);
    *skipsize = off;
    return FALSE;
  }


  offset = 0;
  while (!have_picture) {
    GST_DEBUG ("offset %d:", offset);

    if (offset + 13 >= size) {
      *framesize = offset + 13;
      return FALSE;
    }

    GST_DEBUG ("chunk type %02x", data[offset + 4]);

    if (GST_READ_UINT32_BE (data + offset) != 0x42424344) {
      GST_DEBUG ("bad header");
      *skipsize = 3;
      return FALSE;
    }

    next_header = GST_READ_UINT32_BE (data + offset + 5);
    GST_DEBUG ("next_header %d", next_header);
    if (next_header == 0)
      next_header = 13;

    if (SCHRO_PARSE_CODE_IS_PICTURE (data[offset + 4])) {
      have_picture = TRUE;
    }

    offset += next_header;
    if (offset >= size) {
      *framesize = offset;
      return FALSE;
    }
  }

  *framesize = offset;
  GST_DEBUG ("framesize %d", *framesize);

  return TRUE;
}
