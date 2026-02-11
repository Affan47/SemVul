gst_identity_update_last_message_for_buffer (GstIdentity * identity,
    const gchar * action, GstBuffer * buf, gsize size)
{
  gchar dts_str[64], pts_str[64], dur_str[64];
  gchar flag_str[100];

  GST_OBJECT_LOCK (identity);

  {
    const char *flag_list[15] = {
      "", "", "", "", "live", "decode-only", "discont", "resync", "corrupted",
      "marker", "header", "gap", "droppable", "delta-unit", "in-caps"
    };
    int i;
    char *end = flag_str;
    end[0] = '\0';
    for (i = 0; i < G_N_ELEMENTS (flag_list); i++) {
      if (GST_MINI_OBJECT_CAST (buf)->flags & (1 << i)) {
        strcpy (end, flag_list[i]);
        end += strlen (end);
        end[0] = ' ';
        end[1] = '\0';
        end++;
      }
    }
  }

  g_free (identity->last_message);
  identity->last_message = g_strdup_printf ("%s   ******* (%s:%s) "
      "(%" G_GSIZE_FORMAT " bytes, dts: %s, pts:%s, duration: %s, offset: %"
      G_GINT64_FORMAT ", " "offset_end: % " G_GINT64_FORMAT
      ", flags: %08x %s) %p", action,
      GST_DEBUG_PAD_NAME (GST_BASE_TRANSFORM_CAST (identity)->sinkpad), size,
      print_pretty_time (dts_str, sizeof (dts_str), GST_BUFFER_DTS (buf)),
      print_pretty_time (pts_str, sizeof (pts_str), GST_BUFFER_PTS (buf)),
      print_pretty_time (dur_str, sizeof (dur_str), GST_BUFFER_DURATION (buf)),
      GST_BUFFER_OFFSET (buf), GST_BUFFER_OFFSET_END (buf),
      GST_BUFFER_FLAGS (buf), flag_str, buf);

  GST_OBJECT_UNLOCK (identity);

  gst_identity_notify_last_message (identity);
}
