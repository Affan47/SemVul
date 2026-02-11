gst_dash_demux_download_header_fragment (GstDashDemux * demux, guint stream_idx,
    gchar * path, gint64 range_start, gint64 range_end)
{
  GstBuffer *buffer = NULL;
  gchar *next_header_uri;
  GstFragment *fragment;

  if (strncmp (path, "http://", 7) != 0) {
    next_header_uri =
        g_strconcat (gst_mpdparser_get_baseURL (demux->client, stream_idx),
        path, NULL);
    g_free (path);
  } else {
    next_header_uri = path;
  }

  fragment = gst_uri_downloader_fetch_uri_with_range (demux->downloader,
      next_header_uri, range_start, range_end);
  g_free (next_header_uri);
  if (fragment) {
    buffer = gst_fragment_get_buffer (fragment);
    g_object_unref (fragment);
  }
  return buffer;
}
