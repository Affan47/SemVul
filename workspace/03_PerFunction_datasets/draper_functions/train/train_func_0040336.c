gst_ogg_demux_sync_streams (GstOggDemux * ogg)
{
  GstClockTime cur;
  GstOggChain *chain;
  guint i;

  chain = ogg->current_chain;
  cur = ogg->segment.position;
  if (chain == NULL || cur == -1)
    return;

  for (i = 0; i < chain->streams->len; i++) {
    GstOggPad *stream = g_array_index (chain->streams, GstOggPad *, i);


    if (stream->map.is_sparse && stream->position != GST_CLOCK_TIME_NONE) {


      if (GST_CLOCK_DIFF (stream->position, cur) > (2 * GST_SECOND)) {
        GST_DEBUG_OBJECT (stream, "synchronizing stream with others by "
            "advancing time from %" GST_TIME_FORMAT " to %" GST_TIME_FORMAT,
            GST_TIME_ARGS (stream->position), GST_TIME_ARGS (cur));

        stream->position = cur;

        gst_pad_push_event (GST_PAD_CAST (stream),
            gst_event_new_gap (stream->position, cur - stream->position));
      }
    }
  }
}
