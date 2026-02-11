gst_audioringbuffer_acquire (GstRingBuffer * buf, GstRingBufferSpec * spec)
{
  GstAudioSink *sink;
  GstAudioSinkClass *csink;
  gboolean result = FALSE;

  sink = GST_AUDIO_SINK (GST_OBJECT_PARENT (buf));
  csink = GST_AUDIO_SINK_GET_CLASS (sink);

  if (csink->prepare)
    result = csink->prepare (sink, spec);
  if (!result)
    goto could_not_prepare;


  spec->seglatency = spec->segtotal + 1;

  buf->data = gst_buffer_new_and_alloc (spec->segtotal * spec->segsize);
  memset (GST_BUFFER_DATA (buf->data), 0, GST_BUFFER_SIZE (buf->data));

  return TRUE;


could_not_prepare:
  {
    GST_DEBUG_OBJECT (sink, "could not prepare device");
    return FALSE;
  }
}
