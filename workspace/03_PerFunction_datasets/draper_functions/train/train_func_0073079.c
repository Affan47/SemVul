gst_cmml_dec_sink_query (GstPad * pad, GstQuery * query)
{
  gboolean res = FALSE;

  switch (GST_QUERY_TYPE (query)) {
    case GST_QUERY_CONVERT:
    {
      GstFormat src_fmt, dest_fmt;
      gint64 src_val, dest_val;

      gst_query_parse_convert (query, &src_fmt, &src_val, &dest_fmt, &dest_val);
      res = gst_cmml_dec_convert (pad, src_fmt, src_val, &dest_fmt, &dest_val);
      if (res)
        gst_query_set_convert (query, src_fmt, src_val, dest_fmt, dest_val);
      break;
    }
    default:
      break;
  }

  return res;
}
