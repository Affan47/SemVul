add_uri_tag (GstId3v2Tag * id3v2tag, const GstTagList * list,
    const gchar * tag, guint num_tags, const gchar * frame_id)
{
  const gchar *url = NULL;

  g_assert (frame_id != NULL);


  if (gst_tag_list_peek_string_index (list, tag, 0, &url) && url != NULL) {
    guint url_len;

    url_len = strlen (url);
    if (url_len > 0 && gst_uri_is_valid (url)) {
      GstId3v2Frame frame;

      id3v2_frame_init (&frame, frame_id, 0);
      id3v2_frame_write_bytes (&frame, (const guint8 *) url, strlen (url) + 1);
      g_array_append_val (id3v2tag->frames, frame);
    } else {
      GST_WARNING ("Tag %s does not contain a valid URI (%s)", tag, url);
    }
  }
}
