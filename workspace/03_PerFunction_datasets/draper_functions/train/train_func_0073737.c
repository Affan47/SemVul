gst_y4m_dec_src_query (GstPad * pad, GstQuery * query)
{
  GstY4mDec *y4mdec = GST_Y4M_DEC (gst_pad_get_parent (pad));
  gboolean res = FALSE;

  switch (GST_QUERY_TYPE (query)) {
    case GST_QUERY_DURATION:
    {
      GstFormat format;
      GstPad *peer;

      GST_DEBUG ("duration query");

      gst_query_parse_duration (query, &format, NULL);

      if (format != GST_FORMAT_TIME) {
        res = FALSE;
        GST_DEBUG_OBJECT (y4mdec, "not handling duration query in format %d",
            format);
        break;
      }

      peer = gst_pad_get_peer (y4mdec->sinkpad);
      if (peer) {
        GstQuery *peer_query = gst_query_new_duration (GST_FORMAT_BYTES);

        res = gst_pad_query (peer, peer_query);
        if (res) {
          gint64 duration;
          int n_frames;

          gst_query_parse_duration (peer_query, &format, &duration);

          n_frames = gst_y4m_dec_bytes_to_frames (y4mdec, duration);
          GST_DEBUG ("duration in frames %d", n_frames);

          duration = gst_y4m_dec_frames_to_timestamp (y4mdec, n_frames);
          GST_DEBUG ("duration in time %" GST_TIME_FORMAT,
              GST_TIME_ARGS (duration));

          gst_query_set_duration (query, GST_FORMAT_TIME, duration);
          res = TRUE;
        }

        gst_query_unref (peer_query);
        gst_object_unref (peer);
      }
      break;
    }
    default:
      res = gst_pad_query_default (pad, query);
      break;
  }

  gst_object_unref (y4mdec);
  return res;
}
