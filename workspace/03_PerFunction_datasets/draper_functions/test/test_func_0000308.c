tp_base_channel_register (TpBaseChannel *chan)
{
  TpDBusDaemon *bus = tp_base_connection_get_dbus_daemon (chan->priv->conn);

  g_assert (chan->priv->object_path != NULL);
  g_return_if_fail (!chan->priv->registered);

  tp_dbus_daemon_register_object (bus, chan->priv->object_path, chan);
  chan->priv->registered = TRUE;
}
