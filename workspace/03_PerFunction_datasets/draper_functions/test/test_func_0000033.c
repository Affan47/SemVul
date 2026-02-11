gst_sub_parse_src_query (GstPad * pad, GstQuery * query)
{
  GstSubParse *self = GST_SUBPARSE (gst_pad_get_parent (pad));
  gboolean ret = FALSE;

  GST_DEBUG ("Handling %s query", GST_QUERY_TYPE_NAME (query));

  switch (GST_QUERY_TYPE (query)) {
    case GST_QUERY_POSITION:{
      GstFormat fmt;

      gst_query_parse_position (query, &fmt, NULL);
      if (fmt != GST_FORMAT_TIME) {
        ret = gst_pad_peer_query (self->sinkpad, query);
      } else {
        ret = TRUE;
        gst_query_set_position (query, GST_FORMAT_TIME,
            self->segment.last_stop);
      }
      break;
    }
    case GST_QUERY_SEEKING:
    {
      GstFormat fmt;
      gboolean seekable = FALSE;

      ret = TRUE;

      gst_query_parse_seeking (query, &fmt, NULL, NULL, NULL);
      if (fmt == GST_FORMAT_TIME) {
        GstQuery *peerquery = gst_query_new_seeking (GST_FORMAT_BYTES);

        seekable = gst_pad_peer_query (self->sinkpad, peerquery);
        if (seekable)
          gst_query_parse_seeking (peerquery, NULL, &seekable, NULL, NULL);
        gst_query_unref (peerquery);
      }

      gst_query_set_seeking (query, fmt, seekable, seekable ? 0 : -1, -1);
      break;
    }
    default:
      ret = gst_pad_peer_query (self->sinkpad, query);
      break;
  }

  gst_object_unref (self);

  return ret;
}
