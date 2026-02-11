gst_fd_sink_query (GstBaseSink * bsink, GstQuery * query)
{
  gboolean res = FALSE;
  GstFdSink *fdsink;

  fdsink = GST_FD_SINK (bsink);

  switch (GST_QUERY_TYPE (query)) {
    case GST_QUERY_POSITION:
    {
      GstFormat format;

      gst_query_parse_position (query, &format, NULL);

      switch (format) {
        case GST_FORMAT_DEFAULT:
        case GST_FORMAT_BYTES:
          gst_query_set_position (query, GST_FORMAT_BYTES, fdsink->current_pos);
          res = TRUE;
          break;
        default:
          break;
      }
      break;
    }
    case GST_QUERY_FORMATS:
      gst_query_set_formats (query, 2, GST_FORMAT_DEFAULT, GST_FORMAT_BYTES);
      res = TRUE;
      break;
    case GST_QUERY_URI:
      gst_query_set_uri (query, fdsink->uri);
      res = TRUE;
      break;
    case GST_QUERY_SEEKING:{
      GstFormat format;

      gst_query_parse_seeking (query, &format, NULL, NULL, NULL);
      if (format == GST_FORMAT_BYTES || format == GST_FORMAT_DEFAULT) {
        gst_query_set_seeking (query, GST_FORMAT_BYTES, fdsink->seekable, 0,
            -1);
      } else {
        gst_query_set_seeking (query, format, FALSE, 0, -1);
      }
      res = TRUE;
      break;
    }
    default:
      res = GST_BASE_SINK_CLASS (parent_class)->query (bsink, query);
      break;

  }
  return res;
}
