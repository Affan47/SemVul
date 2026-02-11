mxf_mpeg_is_mpeg2_frame (GstBuffer * buffer)
{
  GstByteReader reader = GST_BYTE_READER_INIT_FROM_BUFFER (buffer);
  guint32 tmp;

  while (gst_byte_reader_get_remaining (&reader) > 3) {
    if (gst_byte_reader_peek_uint24_be (&reader, &tmp) && tmp == 0x000001) {
      guint8 type = 0;


      gst_byte_reader_skip (&reader, 3);

      if (!gst_byte_reader_get_uint8 (&reader, &type))
        break;


      if (type == 0x00) {
        return TRUE;
      }
    } else {
      gst_byte_reader_skip (&reader, 1);
    }
  }

  return FALSE;
}
