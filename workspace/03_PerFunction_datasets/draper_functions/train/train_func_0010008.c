nm_supplicant_manager_init (NMSupplicantManager *self)
{
	NMSupplicantManagerPrivate *priv = NM_SUPPLICANT_MANAGER_GET_PRIVATE (self);
	DBusGConnection *bus;

	priv->dbus_mgr = nm_dbus_manager_get ();
	priv->name_owner_id = g_signal_connect (priv->dbus_mgr,
	                                        NM_DBUS_MANAGER_NAME_OWNER_CHANGED,
	                                        G_CALLBACK (name_owner_changed),
	                                        self);
	priv->running = nm_dbus_manager_name_has_owner (priv->dbus_mgr, WPAS_DBUS_SERVICE);

	bus = nm_dbus_manager_get_connection (priv->dbus_mgr);
	priv->proxy = dbus_g_proxy_new_for_name (bus,
	                                         WPAS_DBUS_SERVICE,
	                                         WPAS_DBUS_PATH,
	                                         WPAS_DBUS_INTERFACE);

	priv->props_proxy = dbus_g_proxy_new_for_name (bus,
	                                               WPAS_DBUS_SERVICE,
	                                               WPAS_DBUS_PATH,
	                                               DBUS_INTERFACE_PROPERTIES);

	priv->ifaces = g_hash_table_new_full (g_str_hash, g_str_equal, g_free, g_object_unref);


	if (priv->running)
		check_capabilities (self);
}
