gst_audioringbuffer_acquire (GstRingBuffer * buf, GstRingBufferSpec * spec)
{
  GstAudioSrc *src;
  GstAudioSrcClass *csrc;
  GstAudioRingBuffer *abuf;
  gboolean result = FALSE;

  src = GST_AUDIO_SRC (GST_OBJECT_PARENT (buf));
  csrc = GST_AUDIO_SRC_GET_CLASS (src);

  if (csrc->prepare)
    result = csrc->prepare (src, spec);

  if (!result)
    goto could_not_open;

  buf->data = gst_buffer_new_and_alloc (spec->segtotal * spec->segsize);
  memset (GST_BUFFER_DATA (buf->data), 0, GST_BUFFER_SIZE (buf->data));

  abuf = GST_AUDIORING_BUFFER (buf);
  abuf->running = TRUE;


#if !GLIB_CHECK_VERSION (2, 31, 0)
  src->thread =
      g_thread_create ((GThreadFunc) audioringbuffer_thread_func, buf, TRUE,
      NULL);
#else
  src->thread = g_thread_try_new ("audiosrc-ringbuffer",
      (GThreadFunc) audioringbuffer_thread_func, buf, NULL);
#endif

  GST_AUDIORING_BUFFER_WAIT (buf);

  return result;

could_not_open:
  {
    return FALSE;
  }
}
