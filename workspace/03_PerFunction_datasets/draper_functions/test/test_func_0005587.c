gst_jpeg_parse_app1 (GstJpegParse * parse, GstByteReader * reader)
{
  guint16 size = 0;
  const gchar *id_str;
  const guint8 *data = NULL;

  if (!gst_byte_reader_get_uint16_be (reader, &size))
    return FALSE;

  size -= 2;
  if (!gst_byte_reader_peek_string_utf8 (reader, &id_str))
    return FALSE;

  if (!strncmp (id_str, "Exif", 4)) {


    if (!gst_byte_reader_skip (reader, 6))
      return FALSE;
    size -= 6;


    if (!gst_byte_reader_get_data (reader, size, &data))
      return FALSE;

    extract_and_queue_tags (parse, size, (guint8 *) data,
        gst_tag_list_from_exif_buffer_with_tiff_header);

    GST_LOG_OBJECT (parse, "parsed marker %x: '%s' %u bytes",
        APP1, id_str, size);

  } else if (!strncmp (id_str, "http://ns.adobe.com/xap/1.0/", 28)) {


    if (!gst_byte_reader_skip (reader, 29))
      return FALSE;
    size -= 29;


    if (!gst_byte_reader_get_data (reader, size, &data))
      return FALSE;

    extract_and_queue_tags (parse, size, (guint8 *) data,
        gst_tag_list_from_xmp_buffer);

    GST_LOG_OBJECT (parse, "parsed marker %x: '%s' %u bytes",
        APP1, id_str, size);

  } else {
    if (!gst_jpeg_parse_skip_marker (parse, reader, APP1))
      return FALSE;
  }

  return TRUE;
}
