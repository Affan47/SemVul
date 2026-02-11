gst_rtmp_sink_uri_set_uri (GstURIHandler * handler, const gchar * uri)
{
  GstRTMPSink *sink = GST_RTMP_SINK (handler);

  if (GST_STATE (sink) >= GST_STATE_PAUSED)
    return FALSE;

  g_free (sink->uri);
  sink->uri = NULL;

  if (uri != NULL) {
    int protocol;
    AVal host;
    unsigned int port;
    AVal playpath, app;

    if (!RTMP_ParseURL (uri, &protocol, &host, &port, &playpath, &app) ||
        !host.av_len || !playpath.av_len) {
      GST_ELEMENT_ERROR (sink, RESOURCE, OPEN_WRITE,
          ("Failed to parse URI %s", uri), (NULL));
      return FALSE;
    }
    sink->uri = g_strdup (uri);
  }

  GST_DEBUG_OBJECT (sink, "Changed URI to %s", GST_STR_NULL (uri));

  return TRUE;
}
