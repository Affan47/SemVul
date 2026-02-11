gst_gio_base_sink_query (GstPad * pad, GstQuery * query)
{
  GstGioBaseSink *sink = GST_GIO_BASE_SINK (GST_PAD_PARENT (pad));
  GstFormat format;

  switch (GST_QUERY_TYPE (query)) {
    case GST_QUERY_POSITION:
      gst_query_parse_position (query, &format, NULL);
      switch (format) {
        case GST_FORMAT_BYTES:
        case GST_FORMAT_DEFAULT:
          gst_query_set_position (query, GST_FORMAT_BYTES, sink->position);
          return TRUE;
        default:
          return FALSE;
      }
    case GST_QUERY_FORMATS:
      gst_query_set_formats (query, 2, GST_FORMAT_DEFAULT, GST_FORMAT_BYTES);
      return TRUE;
    case GST_QUERY_URI:
      if (GST_IS_URI_HANDLER (sink)) {
        const gchar *uri;

        uri = gst_uri_handler_get_uri (GST_URI_HANDLER (sink));
        gst_query_set_uri (query, uri);
        return TRUE;
      }
      return FALSE;
    default:
      return gst_pad_query_default (pad, query);
  }
}
