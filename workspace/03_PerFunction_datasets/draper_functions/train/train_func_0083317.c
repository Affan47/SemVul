gst_qtdemux_sync_streams (GstQTDemux * demux)
{
  gint i;

  if (demux->n_streams <= 1)
    return;

  for (i = 0; i < demux->n_streams; i++) {
    QtDemuxStream *stream;
    GstClockTime end_time;

    stream = demux->streams[i];

    if (!stream->pad)
      continue;


    if (demux->segment.flags & GST_SEEK_FLAG_SEGMENT)
      continue;

    if (demux->pullbased) {

      if (!STREAM_IS_EOS (stream))
        continue;
    } else {

      if (stream->n_samples &&
          stream->samples[stream->n_samples - 1].offset >= demux->offset)
        continue;
    }

    if (stream->sent_eos)
      continue;


    end_time = stream->segments[stream->n_segments - 1].stop_time;
    GST_LOG_OBJECT (demux, "current position: %" GST_TIME_FORMAT
        ", stream end: %" GST_TIME_FORMAT,
        GST_TIME_ARGS (demux->segment.position), GST_TIME_ARGS (end_time));
    if (GST_CLOCK_TIME_IS_VALID (end_time)
        && (end_time + 2 * GST_SECOND < demux->segment.position)) {
      GST_DEBUG_OBJECT (demux, "sending EOS for stream %s",
          GST_PAD_NAME (stream->pad));
      stream->sent_eos = TRUE;
      gst_pad_push_event (stream->pad, gst_event_new_eos ());
    }
  }
}
