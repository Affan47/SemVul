gst_ogg_print (GstOggDemux * ogg)
{
  guint j, i;

  GST_INFO_OBJECT (ogg, "%u chains", ogg->chains->len);
  GST_INFO_OBJECT (ogg, " total time: %" GST_TIME_FORMAT,
      GST_TIME_ARGS (ogg->total_time));

  for (i = 0; i < ogg->chains->len; i++) {
    GstOggChain *chain = g_array_index (ogg->chains, GstOggChain *, i);

    GST_INFO_OBJECT (ogg, " chain %d (%u streams):", i, chain->streams->len);
    GST_INFO_OBJECT (ogg,
        "  offset: %" G_GINT64_FORMAT " - %" G_GINT64_FORMAT, chain->offset,
        chain->end_offset);
    GST_INFO_OBJECT (ogg, "  begin time: %" GST_TIME_FORMAT,
        GST_TIME_ARGS (chain->begin_time));
    GST_INFO_OBJECT (ogg, "  total time: %" GST_TIME_FORMAT,
        GST_TIME_ARGS (chain->total_time));
    GST_INFO_OBJECT (ogg, "  segment start: %" GST_TIME_FORMAT,
        GST_TIME_ARGS (chain->segment_start));
    GST_INFO_OBJECT (ogg, "  segment stop:  %" GST_TIME_FORMAT,
        GST_TIME_ARGS (chain->segment_stop));

    for (j = 0; j < chain->streams->len; j++) {
      GstOggPad *stream = g_array_index (chain->streams, GstOggPad *, j);

      GST_INFO_OBJECT (ogg, "  stream %08x: %s", stream->map.serialno,
          gst_ogg_stream_get_media_type (&stream->map));
      GST_INFO_OBJECT (ogg, "   start time:       %" GST_TIME_FORMAT,
          GST_TIME_ARGS (stream->start_time));
    }
  }
}
