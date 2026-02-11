ofono_appeared (NMModemManager *self, gboolean enumerate_devices)
{
	if (self->priv->poke_id) {
		g_source_remove (self->priv->poke_id);
		self->priv->poke_id = 0;
	}

	nm_log_info (LOGD_MB, "ofono is now available");

	self->priv->proxy = dbus_g_proxy_new_for_name (nm_dbus_manager_get_connection (self->priv->dbus_mgr),
	                                               OFONO_DBUS_SERVICE, OFONO_DBUS_PATH, OFONO_DBUS_INTERFACE);

	dbus_g_object_register_marshaller (_nm_marshal_VOID__STRING_BOXED,
	                                   G_TYPE_NONE,
	                                   DBUS_TYPE_G_OBJECT_PATH, DBUS_TYPE_G_MAP_OF_VARIANT,
	                                   G_TYPE_INVALID);
	dbus_g_proxy_add_signal (self->priv->proxy, "ModemAdded", DBUS_TYPE_G_OBJECT_PATH, DBUS_TYPE_G_MAP_OF_VARIANT, G_TYPE_INVALID);
	dbus_g_proxy_connect_signal (self->priv->proxy, "ModemAdded",
								 G_CALLBACK (ofono_modem_added), self,
								 NULL);

	dbus_g_proxy_add_signal (self->priv->proxy, "ModemRemoved", DBUS_TYPE_G_OBJECT_PATH, G_TYPE_INVALID);
	dbus_g_proxy_connect_signal (self->priv->proxy, "ModemRemoved",
								 G_CALLBACK (modem_removed), self,
								 NULL);

	if (enumerate_devices)
		dbus_g_proxy_begin_call (self->priv->proxy, "GetModems", ofono_enumerate_devices_done, self, NULL, G_TYPE_INVALID);
}
