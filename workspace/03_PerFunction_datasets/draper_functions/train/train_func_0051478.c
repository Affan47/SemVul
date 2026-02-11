gst_multi_file_src_query (GstBaseSrc * src, GstQuery * query)
{
  gboolean res;
  GstMultiFileSrc *mfsrc;

  mfsrc = GST_MULTI_FILE_SRC (src);

  switch (GST_QUERY_TYPE (query)) {
    case GST_QUERY_POSITION:
    {
      GstFormat format;

      gst_query_parse_position (query, &format, NULL);
      switch (format) {
        case GST_FORMAT_BUFFERS:
        case GST_FORMAT_DEFAULT:
          gst_query_set_position (query, GST_FORMAT_BUFFERS, mfsrc->index);
          res = TRUE;
          break;
        default:
          res = GST_BASE_SRC_CLASS (parent_class)->query (src, query);
          break;
      }
      break;
    }
    default:
      res = GST_BASE_SRC_CLASS (parent_class)->query (src, query);
      break;
  }
  return res;
}
