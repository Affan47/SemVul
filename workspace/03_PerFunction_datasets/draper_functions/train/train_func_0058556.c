gst_qtdemux_prepare_current_sample (GstQTDemux * qtdemux,
    QtDemuxStream * stream, guint64 * offset, guint * size, guint64 * dts,
    guint64 * pts, guint64 * duration, gboolean * keyframe)
{
  QtDemuxSample *sample;
  guint64 time_position;
  guint32 seg_idx;

  g_return_val_if_fail (stream != NULL, FALSE);

  time_position = stream->time_position;
  if (G_UNLIKELY (time_position == -1))
    goto eos;

  seg_idx = stream->segment_index;
  if (G_UNLIKELY (seg_idx == -1)) {


    seg_idx = gst_qtdemux_find_segment (qtdemux, stream, time_position);


    if (seg_idx == -1)
      goto eos;
  }


  if (G_UNLIKELY (stream->segment_index != seg_idx))
    gst_qtdemux_activate_segment (qtdemux, stream, seg_idx, time_position);

  GST_LOG_OBJECT (qtdemux, "segment active, index = %u of %u",
      stream->sample_index, stream->n_samples);

  if (G_UNLIKELY (stream->sample_index >= stream->n_samples))
    goto eos;

  if (!qtdemux_parse_samples (qtdemux, stream, stream->sample_index)) {
    GST_LOG_OBJECT (qtdemux, "Parsing of index %u failed!",
        stream->sample_index);
    return FALSE;
  }


  sample = &stream->samples[stream->sample_index];

  *dts = QTSAMPLE_DTS (stream, sample);
  *pts = QTSAMPLE_PTS (stream, sample);
  *offset = sample->offset;
  *size = sample->size;
  *duration = QTSAMPLE_DUR_DTS (stream, sample, *dts);
  *keyframe = QTSAMPLE_KEYFRAME (stream, sample);

  return TRUE;


eos:
  {
    stream->time_position = -1;
    return FALSE;
  }
}
