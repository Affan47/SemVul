gst_rtsp_source_finalize (GSource * source)
{
  GstRTSPWatch *watch = (GstRTSPWatch *) source;

  build_reset (&watch->builder);
  gst_rtsp_message_unset (&watch->message);

  g_queue_foreach (watch->messages, (GFunc) gst_rtsp_rec_free, NULL);
  g_queue_free (watch->messages);
  watch->messages = NULL;
  watch->messages_bytes = 0;
  g_free (watch->write_data);

  if (watch->readsrc)
    g_source_unref (watch->readsrc);
  if (watch->writesrc)
    g_source_unref (watch->writesrc);

  g_mutex_clear (&watch->mutex);

  if (watch->notify)
    watch->notify (watch->user_data);
}
