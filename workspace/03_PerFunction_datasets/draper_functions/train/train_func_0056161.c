streams_changed_cb (GObject *stream,
    gpointer spec,
    TpBaseMediaCallChannel *self)
{
  tp_base_media_call_channel_try_accept (self);

  if (self->priv->accepted)
    g_signal_handlers_disconnect_by_func (stream, streams_changed_cb, self);
}
