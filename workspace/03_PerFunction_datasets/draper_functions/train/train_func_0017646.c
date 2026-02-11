gst_qtdemux_loop_state_movie (GstQTDemux * qtdemux)
{
  GstFlowReturn ret = GST_FLOW_OK;
  GstBuffer *buf = NULL;
  QtDemuxStream *stream;
  guint64 min_time;
  guint64 offset = 0;
  guint64 timestamp = GST_CLOCK_TIME_NONE;
  guint64 duration = 0;
  gboolean keyframe = FALSE;
  guint size = 0;
  gint index;
  gint i;

  gst_qtdemux_push_pending_newsegment (qtdemux);


  min_time = G_MAXUINT64;
  index = -1;
  for (i = 0; i < qtdemux->n_streams; i++) {
    guint64 position;

    stream = qtdemux->streams[i];
    position = stream->time_position;


    if (position != -1 && position < min_time) {
      min_time = position;
      index = i;
    }
  }

  if (G_UNLIKELY (index == -1)) {
    GST_DEBUG_OBJECT (qtdemux, "all streams are EOS");
    goto eos;
  }


  if (G_UNLIKELY (qtdemux->segment.stop != -1
          && qtdemux->segment.stop < min_time)) {
    GST_DEBUG_OBJECT (qtdemux, "we reached the end of our segment.");
    goto eos;
  }

  stream = qtdemux->streams[index];


  if (G_UNLIKELY (!gst_qtdemux_prepare_current_sample (qtdemux, stream, &offset,
              &size, &timestamp, &duration, &keyframe)))
    goto eos_stream;

  GST_LOG_OBJECT (qtdemux,
      "pushing from stream %d, offset %" G_GUINT64_FORMAT
      ", size %d, timestamp=%" GST_TIME_FORMAT ", duration %" GST_TIME_FORMAT,
      index, offset, size, GST_TIME_ARGS (timestamp), GST_TIME_ARGS (duration));


  if (G_UNLIKELY (size <= 0))
    goto next;


  if (G_UNLIKELY (stream->last_ret == GST_FLOW_UNEXPECTED))
    goto next;

  GST_LOG_OBJECT (qtdemux, "reading %d bytes @ %" G_GUINT64_FORMAT, size,
      offset);

  ret = gst_qtdemux_pull_atom (qtdemux, offset, size, &buf);
  if (G_UNLIKELY (ret != GST_FLOW_OK))
    goto beach;

  ret = gst_qtdemux_decorate_and_push_buffer (qtdemux, stream, buf,
      timestamp, duration, keyframe, min_time, offset);


  ret = gst_qtdemux_combine_flows (qtdemux, stream, ret);


  if (ret == GST_FLOW_UNEXPECTED)
    ret = GST_FLOW_OK;

next:
  gst_qtdemux_advance_sample (qtdemux, stream);

beach:
  return ret;


eos:
  {
    GST_DEBUG_OBJECT (qtdemux, "No samples left for any streams - EOS");
    ret = GST_FLOW_UNEXPECTED;
    goto beach;
  }
eos_stream:
  {
    GST_DEBUG_OBJECT (qtdemux, "No samples left for stream");

    ret = GST_FLOW_OK;
    goto beach;
  }
}
