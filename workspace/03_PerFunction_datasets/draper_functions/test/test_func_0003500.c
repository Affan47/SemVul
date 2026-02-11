_tp_base_media_call_stream_set_remotely_held (TpBaseMediaCallStream *self,
    gboolean remotely_held)
{
  g_return_if_fail (TP_IS_BASE_MEDIA_CALL_STREAM (self));

  if (remotely_held == self->priv->remotely_held)
    return;

  self->priv->remotely_held = remotely_held;

  tp_base_media_call_stream_update_sending_state (self);
}
