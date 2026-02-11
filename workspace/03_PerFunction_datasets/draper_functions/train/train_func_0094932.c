gst_flups_demux_close_segment (GstFluPSDemux * demux)
{
  gint i, count = demux->found_count;
  GstEvent *event = NULL;
  guint64 base_time;

  GST_INFO_OBJECT (demux, "closing running segment %" GST_SEGMENT_FORMAT,
      &demux->src_segment);


  if ((base_time = demux->base_time) == (guint64) - 1)
    base_time = 0;


  if (demux->src_segment.rate >= 0) {

    event = gst_event_new_new_segment (TRUE,
        demux->src_segment.rate, demux->src_segment.format,
        demux->src_segment.start + base_time,
        demux->src_segment.last_stop + base_time, demux->src_segment.time);
  } else {
    gint64 stop;

    if ((stop = demux->src_segment.stop) == -1)
      stop = demux->src_segment.duration;


    event = gst_event_new_new_segment (TRUE,
        demux->src_segment.rate, demux->src_segment.format,
        demux->src_segment.last_stop + base_time,
        stop + base_time, demux->src_segment.last_stop);
  }

  if (event) {
    for (i = 0; i < count; i++) {
      GstFluPSStream *stream = demux->streams_found[i];

      if (stream && !stream->notlinked && !stream->need_segment) {
        (void) gst_event_ref (event);

        if (!gst_pad_push_event (stream->pad, event)) {
          GST_DEBUG_OBJECT (stream, "event %s was not handled correctly",
              GST_EVENT_TYPE_NAME (event));
        } else {

          GST_DEBUG_OBJECT (stream, "event %s was handled correctly",
              GST_EVENT_TYPE_NAME (event));
        }
      }
    }

    gst_event_unref (event);
  }
}
