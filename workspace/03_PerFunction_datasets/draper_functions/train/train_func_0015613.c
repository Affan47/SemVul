wait_segment (GstAudioRingBuffer * buf)
{
  gint segments;
  gboolean wait = TRUE;


  if (G_UNLIKELY (g_atomic_int_get (&buf->state) !=
          GST_AUDIO_RING_BUFFER_STATE_STARTED)) {

    if (G_UNLIKELY (g_atomic_int_get (&buf->may_start) == FALSE))
      goto no_start;

    GST_DEBUG_OBJECT (buf, "start!");
    segments = g_atomic_int_get (&buf->segdone);
    gst_audio_ring_buffer_start (buf);


    if (G_LIKELY (g_atomic_int_get (&buf->segdone) != segments))
      wait = FALSE;
  }


  GST_OBJECT_LOCK (buf);
  if (G_UNLIKELY (buf->flushing))
    goto flushing;

  if (G_UNLIKELY (g_atomic_int_get (&buf->state) !=
          GST_AUDIO_RING_BUFFER_STATE_STARTED))
    goto not_started;

  if (G_LIKELY (wait)) {
    if (g_atomic_int_compare_and_exchange (&buf->waiting, 0, 1)) {
      GST_DEBUG_OBJECT (buf, "waiting..");
      GST_AUDIO_RING_BUFFER_WAIT (buf);

      if (G_UNLIKELY (buf->flushing))
        goto flushing;

      if (G_UNLIKELY (g_atomic_int_get (&buf->state) !=
              GST_AUDIO_RING_BUFFER_STATE_STARTED))
        goto not_started;
    }
  }
  GST_OBJECT_UNLOCK (buf);

  return TRUE;


not_started:
  {
    g_atomic_int_compare_and_exchange (&buf->waiting, 1, 0);
    GST_DEBUG_OBJECT (buf, "stopped processing");
    GST_OBJECT_UNLOCK (buf);
    return FALSE;
  }
flushing:
  {
    g_atomic_int_compare_and_exchange (&buf->waiting, 1, 0);
    GST_DEBUG_OBJECT (buf, "flushing");
    GST_OBJECT_UNLOCK (buf);
    return FALSE;
  }
no_start:
  {
    GST_DEBUG_OBJECT (buf, "not allowed to start");
    return FALSE;
  }
}
