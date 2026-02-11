fs_rtp_stream_get_stream_transmitter (FsRtpStream *self, GError **error)
{
  FsRtpSession *session = fs_rtp_stream_get_session (self, error);
  FsStreamTransmitter *st = NULL;

  if (!session)
    return NULL;

  FS_RTP_SESSION_LOCK (session);
  st = self->priv->stream_transmitter;
  if (st)
    g_object_ref (st);
  FS_RTP_SESSION_UNLOCK (session);

  if (!st)
    g_set_error (error, FS_ERROR, FS_ERROR_DISPOSED,
        "Stream transmitter not set (or stream has been disposed)");

  g_object_unref (session);
  return st;
}
