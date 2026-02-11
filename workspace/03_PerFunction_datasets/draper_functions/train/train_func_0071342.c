audioringbuffer_thread_func (GstRingBuffer * buf)
{
  GstAudioSrc *src;
  GstAudioSrcClass *csrc;
  GstAudioRingBuffer *abuf = GST_AUDIORING_BUFFER (buf);
  ReadFunc readfunc;
  GstMessage *message;
  GValue val = { 0 };

  src = GST_AUDIO_SRC (GST_OBJECT_PARENT (buf));
  csrc = GST_AUDIO_SRC_GET_CLASS (src);

  GST_DEBUG_OBJECT (src, "enter thread");

  readfunc = csrc->read;
  if (readfunc == NULL)
    goto no_function;


  g_value_init (&val, G_TYPE_POINTER);
  g_value_set_pointer (&val, src->thread);
  message = gst_message_new_stream_status (GST_OBJECT_CAST (buf),
      GST_STREAM_STATUS_TYPE_ENTER, GST_ELEMENT_CAST (src));
  gst_message_set_stream_status_object (message, &val);
  GST_DEBUG_OBJECT (src, "posting ENTER stream status");
  gst_element_post_message (GST_ELEMENT_CAST (src), message);

  while (TRUE) {
    gint left, len;
    guint8 *readptr;
    gint readseg;

    if (gst_ring_buffer_prepare_read (buf, &readseg, &readptr, &len)) {
      gint read;

      left = len;
      do {
        read = readfunc (src, readptr, left);
        GST_LOG_OBJECT (src, "transfered %d bytes of %d to segment %d", read,
            left, readseg);
        if (read < 0 || read > left) {
          GST_WARNING_OBJECT (src,
              "error reading data %d (reason: %s), skipping segment", read,
              g_strerror (errno));
          break;
        }
        left -= read;
        readptr += read;
      } while (left > 0);


      gst_ring_buffer_advance (buf, 1);
    } else {
      GST_OBJECT_LOCK (abuf);
      if (!abuf->running)
        goto stop_running;
      GST_DEBUG_OBJECT (src, "signal wait");
      GST_AUDIORING_BUFFER_SIGNAL (buf);
      GST_DEBUG_OBJECT (src, "wait for action");
      GST_AUDIORING_BUFFER_WAIT (buf);
      GST_DEBUG_OBJECT (src, "got signal");
      if (!abuf->running)
        goto stop_running;
      GST_DEBUG_OBJECT (src, "continue running");
      GST_OBJECT_UNLOCK (abuf);
    }
  }


  g_assert_not_reached ();
  return;


no_function:
  {
    GST_DEBUG ("no write function, exit thread");
    return;
  }
stop_running:
  {
    GST_OBJECT_UNLOCK (abuf);
    GST_DEBUG ("stop running, exit thread");
    message = gst_message_new_stream_status (GST_OBJECT_CAST (buf),
        GST_STREAM_STATUS_TYPE_LEAVE, GST_ELEMENT_CAST (src));
    gst_message_set_stream_status_object (message, &val);
    GST_DEBUG_OBJECT (src, "posting LEAVE stream status");
    gst_element_post_message (GST_ELEMENT_CAST (src), message);
    return;
  }
}
