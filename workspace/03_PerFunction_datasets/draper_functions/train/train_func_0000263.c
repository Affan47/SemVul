gst_audio_sink_ring_buffer_stop (GstAudioRingBuffer * buf)
{
  GstAudioSink *sink;
  GstAudioSinkClass *csink;

  sink = GST_AUDIO_SINK (GST_OBJECT_PARENT (buf));
  csink = GST_AUDIO_SINK_GET_CLASS (sink);


  if (csink->reset) {
    GST_DEBUG_OBJECT (sink, "reset...");
    csink->reset (sink);
    GST_DEBUG_OBJECT (sink, "reset done");
  }
#if 0
  if (abuf->running) {
    GST_DEBUG_OBJECT (sink, "stop, waiting...");
    GST_AUDIO_SINK_RING_BUFFER_WAIT (buf);
    GST_DEBUG_OBJECT (sink, "stopped");
  }
#endif

  return TRUE;
}
