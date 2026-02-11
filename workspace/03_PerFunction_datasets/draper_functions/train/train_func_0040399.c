fs_multicast_stream_transmitter_add_remote_candidate (
    FsMulticastStreamTransmitter *self, FsCandidate *candidate,
    GError **error)
{
  UdpSock *newudpsock = NULL;

  FS_MULTICAST_STREAM_TRANSMITTER_LOCK (self);
  if (self->priv->remote_candidate[candidate->component_id])
  {
    FsCandidate *old_candidate =
      self->priv->remote_candidate[candidate->component_id];
    if (old_candidate->port == candidate->port &&
        old_candidate->ttl == candidate->ttl &&
        !strcmp (old_candidate->ip, candidate->ip))
    {
      GST_DEBUG ("Re-set the same candidate, ignoring");
      FS_MULTICAST_STREAM_TRANSMITTER_UNLOCK (self);
     return TRUE;
    }
  }

  FS_MULTICAST_STREAM_TRANSMITTER_UNLOCK (self);


  newudpsock = fs_multicast_transmitter_get_udpsock (
      self->priv->transmitter,
      candidate->component_id,
      self->priv->local_candidate[candidate->component_id]->ip,
      candidate->ip,
      candidate->port,
      candidate->ttl,
      self->priv->sending,
      error);

  if (!newudpsock)
    return FALSE;

  FS_MULTICAST_STREAM_TRANSMITTER_LOCK (self);

  if (self->priv->udpsocks[candidate->component_id])
  {
    if (self->priv->sending)
      fs_multicast_transmitter_udpsock_dec_sending (
          self->priv->udpsocks[candidate->component_id]);
    fs_multicast_transmitter_put_udpsock (self->priv->transmitter,
        self->priv->udpsocks[candidate->component_id],
        self->priv->remote_candidate[candidate->component_id]->ttl);
  }

  self->priv->udpsocks[candidate->component_id] = newudpsock;

  fs_candidate_destroy (self->priv->remote_candidate[candidate->component_id]);
  self->priv->remote_candidate[candidate->component_id] =
    fs_candidate_copy (candidate);

  FS_MULTICAST_STREAM_TRANSMITTER_UNLOCK (self);

  g_signal_emit_by_name (self, "new-active-candidate-pair",
      self->priv->local_candidate[candidate->component_id],
      self->priv->remote_candidate[candidate->component_id]);

  return TRUE;
}
