_tp_account_channel_request_set_channel_factory (TpAccountChannelRequest *self,
    TpClientChannelFactory *factory)
{
  g_return_if_fail (!self->priv->requested);

  tp_clear_object (&self->priv->factory);

  if (factory != NULL)
    self->priv->factory = g_object_ref (factory);
}
