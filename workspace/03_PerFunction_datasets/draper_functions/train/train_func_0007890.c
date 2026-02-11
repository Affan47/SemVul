gst_flups_demux_send_gap_updates (GstFluPSDemux * demux, GstClockTime new_time)
{
  gint id;
  GstEvent *event = NULL;


  if (new_time > demux->src_segment.stop)
    return;

  for (id = 0; id < GST_FLUPS_DEMUX_MAX_STREAMS; id++) {
    GstFluPSStream *stream = demux->streams[id];

    if (stream) {
      if (stream->last_ts == GST_CLOCK_TIME_NONE ||
          stream->last_ts < demux->src_segment.start)
        stream->last_ts = demux->src_segment.start;
      if (stream->last_ts + stream->segment_thresh < new_time) {
#if 0
        g_print ("Gap event update to pad %s from time %" GST_TIME_FORMAT
            " to %" GST_TIME_FORMAT "\n", GST_PAD_NAME (stream->pad),
            GST_TIME_ARGS (stream->last_ts), GST_TIME_ARGS (new_time));
#endif
        GST_DEBUG_OBJECT (demux,
            "Gap event update to pad %s from time %" GST_TIME_FORMAT " to %"
            GST_TIME_FORMAT, GST_PAD_NAME (stream->pad),
            GST_TIME_ARGS (stream->last_ts), GST_TIME_ARGS (new_time));
        event = gst_event_new_gap (stream->last_ts, new_time - stream->last_ts);
        gst_pad_push_event (stream->pad, event);
        stream->last_seg_start = stream->last_ts = new_time;
      }
    }
  }
}
