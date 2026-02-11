gst_freeverb_transform (GstBaseTransform * base, GstBuffer * inbuf,
    GstBuffer * outbuf)
{
  GstFreeverb *filter = GST_FREEVERB (base);
  guint num_samples;
  GstClockTime timestamp;
  GstMapInfo inmap, outmap;

  timestamp = GST_BUFFER_TIMESTAMP (inbuf);
  timestamp =
      gst_segment_to_stream_time (&base->segment, GST_FORMAT_TIME, timestamp);

  gst_buffer_map (inbuf, &inmap, GST_MAP_READ);
  gst_buffer_map (outbuf, &outmap, GST_MAP_WRITE);
  num_samples = outmap.size / (2 * GST_AUDIO_INFO_BPS (&filter->info));

  GST_DEBUG_OBJECT (filter, "processing %u samples at %" GST_TIME_FORMAT,
      num_samples, GST_TIME_ARGS (timestamp));

  if (GST_CLOCK_TIME_IS_VALID (timestamp))
    gst_object_sync_values (GST_OBJECT (filter), timestamp);

  if (G_UNLIKELY (GST_BUFFER_FLAG_IS_SET (inbuf, GST_BUFFER_FLAG_DISCONT))) {
    filter->drained = FALSE;
  }
  if (G_UNLIKELY (GST_BUFFER_FLAG_IS_SET (inbuf, GST_BUFFER_FLAG_GAP))) {
    if (filter->drained) {
      memset (outmap.data, 0, outmap.size);
    }
  } else {
    filter->drained = FALSE;
  }

  if (!filter->drained) {
    filter->drained =
        filter->process (filter, inmap.data, outmap.data, num_samples);
  }

  if (filter->drained) {
    GST_BUFFER_FLAG_SET (outbuf, GST_BUFFER_FLAG_GAP);
  }

  gst_buffer_unmap (inbuf, &inmap);
  gst_buffer_unmap (outbuf, &outmap);

  return GST_FLOW_OK;
}
