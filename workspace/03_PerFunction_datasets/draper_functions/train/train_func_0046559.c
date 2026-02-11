gst_shm_sink_stop (GstBaseSink * bsink)
{
  GstShmSink *self = GST_SHM_SINK (bsink);

  self->stop = TRUE;
  gst_poll_set_flushing (self->poll, TRUE);

  if (self->allocator)
    gst_object_unref (self->allocator);
  self->allocator = NULL;

  g_thread_join (self->pollthread);
  self->pollthread = NULL;

  GST_DEBUG_OBJECT (self, "Stopping");

  while (self->clients) {
    struct GstShmClient *client = self->clients->data;
    self->clients = g_list_remove (self->clients, client);
    sp_writer_close_client (self->pipe, client->client,
        (sp_buffer_free_callback) gst_buffer_unref, NULL);
    g_signal_emit (self, signals[SIGNAL_CLIENT_DISCONNECTED], 0,
        client->pollfd.fd);
    g_slice_free (struct GstShmClient, client);
  }

  gst_poll_free (self->poll);
  self->poll = NULL;

  sp_writer_close (self->pipe, NULL, NULL);
  self->pipe = NULL;

  return TRUE;
}
