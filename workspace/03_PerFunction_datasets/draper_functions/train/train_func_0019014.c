gst_flups_demux_send_gap_updates (GstFluPSDemux * demux, GstClockTime new_start)
{
  GstClockTime base_time, stop;
  gint i, count = demux->found_count;
  GstEvent *event = NULL;


  if ((base_time = demux->base_time) == GST_CLOCK_TIME_NONE)
    base_time = 0;

  stop = demux->src_segment.stop;
  if (stop != GST_CLOCK_TIME_NONE)
    stop += base_time;

  if (new_start > stop)
    return;


  for (i = 0; i < count; i++) {
    GstFluPSStream *stream = demux->streams_found[i];

    if (stream) {
      if (stream->last_ts == GST_CLOCK_TIME_NONE ||
          stream->last_ts < demux->src_segment.start + base_time)
        stream->last_ts = demux->src_segment.start + base_time;

      if (stream->last_ts + stream->segment_thresh < new_start) {

        gst_flups_demux_send_segment (demux, stream, GST_CLOCK_TIME_NONE);

        GST_LOG_OBJECT (demux,
            "Sending gap update to pad %s time %" GST_TIME_FORMAT,
            GST_PAD_NAME (stream->pad), GST_TIME_ARGS (new_start));
        event =
            gst_event_new_gap (stream->last_ts, new_start - stream->last_ts);
        gst_pad_push_event (stream->pad, event);
        stream->last_ts = new_start;
      }
    }
  }
}
