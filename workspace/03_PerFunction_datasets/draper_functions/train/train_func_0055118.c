gst_nsfdec_src_query (GstPad * pad, GstQuery * query)
{
  gboolean res = TRUE;
  GstNsfDec *nsfdec;

  nsfdec = GST_NSFDEC (gst_pad_get_parent (pad));

  switch (GST_QUERY_TYPE (query)) {
    case GST_QUERY_POSITION:
    {
      GstFormat format;
      gint64 current;

      gst_query_parse_position (query, &format, NULL);


      res &= gst_nsfdec_src_convert (pad,
          GST_FORMAT_BYTES, nsfdec->total_bytes, &format, &current);
      if (res) {
        gst_query_set_position (query, format, current);
      }
      break;
    }
    default:
      res = gst_pad_query_default (pad, query);
      break;
  }
  gst_object_unref (nsfdec);

  return res;
}
