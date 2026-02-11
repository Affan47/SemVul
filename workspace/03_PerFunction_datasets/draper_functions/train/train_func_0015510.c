fs_msn_session_dispose (GObject *object)
{
  FsMsnSession *self = FS_MSN_SESSION (object);
  GstBin *conferencebin = NULL;
  FsMsnConference *conference = fs_msn_session_get_conference (self, NULL);
  GstElement *valve = NULL;

  g_mutex_lock (&self->priv->mutex);
  self->priv->conference = NULL;
  g_mutex_unlock (&self->priv->mutex);

  if (!conference)
    goto out;

  if (self->priv->stream)
  {
    g_object_weak_unref (G_OBJECT (self->priv->stream), _remove_stream, self);
    fs_stream_destroy (FS_STREAM (self->priv->stream));
    self->priv->stream = NULL;
  }

  conferencebin = GST_BIN (conference);

  if (!conferencebin)
    goto out;

  if (self->priv->media_sink_pad)
    gst_pad_set_active (self->priv->media_sink_pad, FALSE);

  GST_OBJECT_LOCK (conference);
  valve = self->valve;
  self->valve = NULL;
  GST_OBJECT_UNLOCK (conference);

  if (valve)
  {
    gst_element_set_locked_state (valve, TRUE);
    gst_element_set_state (valve, GST_STATE_NULL);
    gst_bin_remove (conferencebin, valve);
  }

  if (self->priv->media_sink_pad)
    gst_element_remove_pad (GST_ELEMENT (conference),
        self->priv->media_sink_pad);
  self->priv->media_sink_pad = NULL;

  gst_object_unref (conferencebin);
  gst_object_unref (conference);

 out:

  G_OBJECT_CLASS (fs_msn_session_parent_class)->dispose (object);
}
