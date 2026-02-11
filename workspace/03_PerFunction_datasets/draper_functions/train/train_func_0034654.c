fs_shm_transmitter_get_shm_src (FsShmTransmitter *self,
    guint component,
    const gchar *path,
    got_buffer got_buffer_func,
    connection disconnected_func,
    gpointer cb_data,
    GError **error)
{
  ShmSrc *shm = g_slice_new0 (ShmSrc);
  GstElement *elem;
  GstPad *pad;

  shm->component = component;
  shm->got_buffer_func = got_buffer_func;
  shm->disconnected_func = disconnected_func;
  shm->cb_data = cb_data;

  shm->path = g_strdup (path);

  elem = gst_element_factory_make ("shmsrc", NULL);
  if (!elem)
  {
    g_set_error (error, FS_ERROR, FS_ERROR_CONSTRUCTION,
        "Could not make shmsrc");
    goto error;
  }

  g_object_set (elem,
      "socket-path", path,
      "do-timestamp", self->priv->do_timestamp,
      "is-live", TRUE,
      NULL);

  if (shm->disconnected_func)
    g_signal_connect (self->priv->gst_src, "disconnected",
        G_CALLBACK (disconnected_cb), shm);

  if (!gst_bin_add (GST_BIN (self->priv->gst_src), elem))
  {
    g_set_error (error, FS_ERROR, FS_ERROR_CONSTRUCTION,
        "Could not add recvonly filter to bin");
    gst_object_unref (elem);
    goto error;
  }

  shm->src = elem;

  shm->funnelpad = gst_element_get_request_pad (self->priv->funnels[component],
      "sink_%u");

  if (!shm->funnelpad)
  {
    g_set_error (error, FS_ERROR, FS_ERROR_CONSTRUCTION,
        "Could not get funnelpad");
    goto error;
  }

  pad = gst_element_get_static_pad (shm->src, "src");
  if (GST_PAD_LINK_FAILED (gst_pad_link (pad, shm->funnelpad)))
  {
    g_set_error (error, FS_ERROR, FS_ERROR_CONSTRUCTION, "Could not link tee"
        " and valve");
    gst_object_unref (pad);
    goto error;
  }

  gst_object_unref (pad);

  if (got_buffer_func)
    shm->buffer_probe = gst_pad_add_probe (shm->funnelpad,
        GST_PAD_PROBE_TYPE_BUFFER,
        src_buffer_probe_cb, shm, NULL);

  if (!gst_element_sync_state_with_parent (shm->src))
  {
    g_set_error (error, FS_ERROR, FS_ERROR_CONSTRUCTION,
        "Could not sync the state of the new shmsrc with its parent");
    goto error;
  }

  return shm;

 error:
  fs_shm_transmitter_check_shm_src (self, shm, NULL);
  return NULL;
}
