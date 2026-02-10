gst_ring_buffer_debug_spec_buff (GstRingBufferSpec * spec)
{
  GST_DEBUG ("acquire ringbuffer: buffer time: %" G_GINT64_FORMAT " usec",
      spec->buffer_time);
  GST_DEBUG ("acquire ringbuffer: latency time: %" G_GINT64_FORMAT " usec",
      spec->latency_time);
  GST_DEBUG ("acquire ringbuffer: total segments: %d", spec->segtotal);
  GST_DEBUG ("acquire ringbuffer: latency segments: %d", spec->seglatency);
  GST_DEBUG ("acquire ringbuffer: segment size: %d bytes = %d samples",
      spec->segsize, spec->segsize / spec->bytes_per_sample);
  GST_DEBUG ("acquire ringbuffer: buffer size: %d bytes = %d samples",
      spec->segsize * spec->segtotal,
      spec->segsize * spec->segtotal / spec->bytes_per_sample);
}
