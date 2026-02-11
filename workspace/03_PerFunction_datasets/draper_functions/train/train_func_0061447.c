gst_audio_fx_base_iir_filter_transform_ip (GstBaseTransform * base,
    GstBuffer * buf)
{
  GstAudioFXBaseIIRFilter *filter = GST_AUDIO_FX_BASE_IIR_FILTER (base);
  guint num_samples;
  GstClockTime timestamp, stream_time;
  GstMapInfo map;

  timestamp = GST_BUFFER_TIMESTAMP (buf);
  stream_time =
      gst_segment_to_stream_time (&base->segment, GST_FORMAT_TIME, timestamp);

  GST_DEBUG_OBJECT (filter, "sync to %" GST_TIME_FORMAT,
      GST_TIME_ARGS (timestamp));

  if (GST_CLOCK_TIME_IS_VALID (stream_time))
    gst_object_sync_values (GST_OBJECT (filter), stream_time);

  if (filter->a == NULL || filter->b == NULL) {
    g_return_val_if_fail (filter->a != NULL
        && filter->b != NULL, GST_FLOW_ERROR);
    return GST_FLOW_ERROR;
  }

  gst_buffer_map (buf, &map, GST_MAP_READWRITE);
  num_samples = map.size / GST_AUDIO_FILTER_BPS (filter);

  g_mutex_lock (&filter->lock);
  filter->process (filter, map.data, num_samples);
  g_mutex_unlock (&filter->lock);

  gst_buffer_unmap (buf, &map);

  return GST_FLOW_OK;
}
