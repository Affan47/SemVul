gst_audio_echo_transform_ip (GstBaseTransform * base, GstBuffer * buf)
{
  GstAudioEcho *self = GST_AUDIO_ECHO (base);
  guint num_samples;
  GstClockTime timestamp, stream_time;

  timestamp = GST_BUFFER_TIMESTAMP (buf);
  stream_time =
      gst_segment_to_stream_time (&base->segment, GST_FORMAT_TIME, timestamp);

  GST_DEBUG_OBJECT (self, "sync to %" GST_TIME_FORMAT,
      GST_TIME_ARGS (timestamp));

  if (GST_CLOCK_TIME_IS_VALID (stream_time))
    gst_object_sync_values (G_OBJECT (self), stream_time);

  num_samples =
      GST_BUFFER_SIZE (buf) / (GST_AUDIO_FILTER (self)->format.width / 8);

  if (self->buffer == NULL) {
    guint width, rate, channels;

    width = GST_AUDIO_FILTER (self)->format.width / 8;
    rate = GST_AUDIO_FILTER (self)->format.rate;
    channels = GST_AUDIO_FILTER (self)->format.channels;

    self->delay_frames =
        MAX (gst_util_uint64_scale (self->delay, rate, GST_SECOND), 1);
    self->buffer_size_frames =
        MAX (gst_util_uint64_scale (self->max_delay, rate, GST_SECOND), 1);

    self->buffer_size = self->buffer_size_frames * width * channels;
    self->buffer = g_try_malloc0 (self->buffer_size);
    self->buffer_pos = 0;

    if (self->buffer == NULL) {
      GST_ERROR_OBJECT (self, "Failed to allocate %u bytes", self->buffer_size);
      return GST_FLOW_ERROR;
    }
  }

  self->process (self, GST_BUFFER_DATA (buf), num_samples);

  return GST_FLOW_OK;
}
