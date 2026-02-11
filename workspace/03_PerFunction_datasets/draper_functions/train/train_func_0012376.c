fs_rtp_stream_dispose (GObject *object)
{
  FsRtpStream *self = FS_RTP_STREAM (object);
  FsStreamTransmitter *st;
  FsRtpParticipant *participant;
  FsRtpSession *session = fs_rtp_stream_get_session (self, NULL);

  if (!session)
    return;

  g_mutex_lock (&self->priv->mutex);
  self->priv->session = NULL;
  g_mutex_unlock (&self->priv->mutex);

  FS_RTP_SESSION_LOCK (session);

  if (self->priv->sending_changed_locked_cb &&
      self->priv->direction & FS_DIRECTION_SEND)
    self->priv->sending_changed_locked_cb (self, FALSE,
        self->priv->user_data_for_cb);

  participant = self->participant;
  self->participant = NULL;

  st = self->priv->stream_transmitter;
  self->priv->stream_transmitter = NULL;

  if (st)
  {
    g_signal_handler_disconnect (st,
        self->priv->local_candidates_prepared_handler_id);
    g_signal_handler_disconnect (st,
        self->priv->new_active_candidate_pair_handler_id);
    g_signal_handler_disconnect (st,
        self->priv->new_local_candidate_handler_id);
    g_signal_handler_disconnect (st,
        self->priv->error_handler_id);
    g_signal_handler_disconnect (st,
        self->priv->known_source_packet_received_handler_id);
    g_signal_handler_disconnect (st,
        self->priv->state_changed_handler_id);

    FS_RTP_SESSION_UNLOCK (session);
    fs_stream_transmitter_stop (st);
    g_object_unref (st);
    FS_RTP_SESSION_LOCK (session);
  }

  while (self->substreams)
  {
    FsRtpSubStream *substream = self->substreams->data;
    self->substreams = g_list_remove (self->substreams, substream);
    FS_RTP_SESSION_UNLOCK (session);
    g_object_unref (substream);
    FS_RTP_SESSION_LOCK (session);
  }

  FS_RTP_SESSION_UNLOCK (session);

  g_object_unref (participant);
  g_object_unref (session);
  g_object_unref (session);

  G_OBJECT_CLASS (fs_rtp_stream_parent_class)->dispose (object);
}
