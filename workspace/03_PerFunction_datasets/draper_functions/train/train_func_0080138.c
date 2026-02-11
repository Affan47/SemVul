gst_gio_src_query (GstBaseSrc * base_src, GstQuery * query)
{
  gboolean res;
  GstGioSrc *src = GST_GIO_SRC (base_src);

  switch (GST_QUERY_TYPE (query)) {
    case GST_QUERY_SCHEDULING:
    {
      gchar *scheme;
      GstSchedulingFlags flags;

      flags = 0;
      if (src->file == NULL)
        goto forward_parent;

      scheme = g_file_get_uri_scheme (src->file);
      if (scheme == NULL)
        goto forward_parent;

      if (strcmp (scheme, "file") == 0) {
        GST_LOG_OBJECT (src, "local URI, assuming random access is possible");
        flags |= GST_SCHEDULING_FLAG_SEEKABLE;
      } else if (strcmp (scheme, "http") == 0 || strcmp (scheme, "https") == 0) {
        GST_LOG_OBJECT (src, "blacklisted protocol '%s', "
            "no random access possible", scheme);
      } else {
        GST_LOG_OBJECT (src, "unhandled protocol '%s', asking parent", scheme);
        goto forward_parent;
      }
      g_free (scheme);

      gst_query_set_scheduling (query, flags, 1, -1, 0);
      gst_query_add_scheduling_mode (query, GST_PAD_MODE_PUSH);
      if (flags & GST_SCHEDULING_FLAG_SEEKABLE)
        gst_query_add_scheduling_mode (query, GST_PAD_MODE_PULL);

      res = TRUE;
      break;
    }
    default:
    forward_parent:
      res = GST_CALL_PARENT_WITH_DEFAULT (GST_BASE_SRC_CLASS,
          query, (base_src, query), FALSE);
      break;
  }

  return res;
}
