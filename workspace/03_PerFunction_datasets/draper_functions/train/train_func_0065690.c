add_id3v2frame_tag (GstId3v2Tag * id3v2tag, const GstTagList * list,
    const gchar * tag, guint num_tags, const gchar * unused)
{
  guint i;

  for (i = 0; i < num_tags; ++i) {
    const GValue *val;
    GstBuffer *buf;

    val = gst_tag_list_get_value_index (list, tag, i);
    buf = (GstBuffer *) gst_value_get_mini_object (val);

    if (buf && GST_BUFFER_CAPS (buf)) {
      GstStructure *s;
      gint version = 0;

      s = gst_caps_get_structure (GST_BUFFER_CAPS (buf), 0);


      if (s && gst_structure_get_int (s, "version", &version) &&
          version == id3v2tag->major_version) {
        GstId3v2Frame frame;
        gchar frame_id[5];
        guint16 flags;
        guint8 *data = GST_BUFFER_DATA (buf);
        gint size = GST_BUFFER_SIZE (buf);

        if (size < 10)
          return;


        memcpy (frame_id, data, 4);
        frame_id[4] = 0;
        flags = GST_READ_UINT16_BE (data + 8);

        id3v2_frame_init (&frame, frame_id, flags);
        id3v2_frame_write_bytes (&frame, data + 10, size - 10);

        g_array_append_val (id3v2tag->frames, frame);
        GST_DEBUG ("Added unparsed tag with %d bytes", size);
      } else {
        GST_WARNING ("Discarding unrecognised ID3 tag for different ID3 "
            "version");
      }
    }
  }
}
