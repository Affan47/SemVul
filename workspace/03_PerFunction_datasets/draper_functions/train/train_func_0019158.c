dispose (GObject *object)
{
	NMBluezDevice *self = NM_BLUEZ_DEVICE (object);
	NMBluezDevicePrivate *priv = NM_BLUEZ_DEVICE_GET_PRIVATE (self);

	g_slist_foreach (priv->connections, (GFunc) g_object_unref, NULL);
	g_slist_free (priv->connections);
	priv->connections = NULL;

	g_signal_handlers_disconnect_by_func (priv->provider, cp_connection_added, self);
	g_signal_handlers_disconnect_by_func (priv->provider, cp_connection_removed, self);
	g_signal_handlers_disconnect_by_func (priv->provider, cp_connection_updated, self);
	g_signal_handlers_disconnect_by_func (priv->provider, cp_connections_loaded, self);

#if ! WITH_BLUEZ4
	g_clear_object (&priv->adapter);
#endif
	g_clear_object (&priv->dbus_connection);

	G_OBJECT_CLASS (nm_bluez_device_parent_class)->dispose (object);
}
