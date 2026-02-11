_tp_channel_request_set_channel_factory (TpChannelRequest *self,
    TpClientChannelFactory *factory)
{
  tp_clear_object (&self->priv->channel_factory);

  if (factory != NULL)
    self->priv->channel_factory = g_object_ref (factory);
  g_object_notify (G_OBJECT (self), "channel-factory");
}
