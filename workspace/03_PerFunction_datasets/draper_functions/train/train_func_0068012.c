_tp_proxy_will_announce_connected_async (TpProxy *self,
    GAsyncReadyCallback callback,
    gpointer user_data)
{
  g_assert (TP_IS_CONNECTION (self));
  g_assert (self->priv->will_announce_connected_result == NULL);

  self->priv->will_announce_connected_result = g_simple_async_result_new (
      (GObject *) self, callback, user_data,
      _tp_proxy_will_announce_connected_async);

  g_datalist_foreach (&self->priv->features, foreach_feature, self);

  check_announce_connected (self, TRUE);
}
