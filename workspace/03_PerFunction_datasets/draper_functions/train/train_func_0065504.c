gst_value_transform_fourcc_string (const GValue * src_value,
    GValue * dest_value)
{
  guint32 fourcc = src_value->data[0].v_int;
  gchar fourcc_char[4];

  fourcc_char[0] = (fourcc >> 0) & 0xff;
  fourcc_char[1] = (fourcc >> 8) & 0xff;
  fourcc_char[2] = (fourcc >> 16) & 0xff;
  fourcc_char[3] = (fourcc >> 24) & 0xff;

  if ((g_ascii_isalnum (fourcc_char[0]) || fourcc_char[0] == ' ') &&
      (g_ascii_isalnum (fourcc_char[1]) || fourcc_char[1] == ' ') &&
      (g_ascii_isalnum (fourcc_char[2]) || fourcc_char[2] == ' ') &&
      (g_ascii_isalnum (fourcc_char[3]) || fourcc_char[3] == ' ')) {
    dest_value->data[0].v_pointer =
        g_strdup_printf ("%" GST_FOURCC_FORMAT, GST_FOURCC_ARGS (fourcc));
  } else {
    dest_value->data[0].v_pointer = g_strdup_printf ("0x%08x", fourcc);
  }
}
