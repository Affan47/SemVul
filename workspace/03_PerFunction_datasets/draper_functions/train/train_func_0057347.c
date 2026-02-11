id3v2_tag_add_text_frame (GstId3v2Tag * tag, const gchar * frame_id,
    const gchar ** strings_utf8, int num_strings)
{
  GstId3v2Frame frame;
  guint len, i;
  int encoding;

  if (num_strings < 1 || strings_utf8 == NULL || strings_utf8[0] == NULL) {
    GST_LOG ("Not adding text frame, no strings");
    return;
  }

  id3v2_frame_init (&frame, frame_id, 0);

  encoding = id3v2_tag_string_encoding (tag, strings_utf8[0]);
  id3v2_frame_write_uint8 (&frame, encoding);

  GST_LOG ("Adding text frame %s with %d strings", frame_id, num_strings);

  for (i = 0; i < num_strings; ++i) {
    len = strlen (strings_utf8[i]);
    g_return_if_fail (g_utf8_validate (strings_utf8[i], len, NULL));

    id3v2_frame_write_string (&frame, encoding, strings_utf8[i],
        i != num_strings - 1);


    if (tag->major_version < 4)
      break;
  }

  if (i < num_strings - 1) {
    GST_WARNING ("Only wrote one of multiple string values for text frame %s "
        "- ID3v2 supports multiple string values only since v2.4.0, but writing"
        "v2.%u.0 tag", frame_id, tag->major_version);
  }

  g_array_append_val (tag->frames, frame);
}
