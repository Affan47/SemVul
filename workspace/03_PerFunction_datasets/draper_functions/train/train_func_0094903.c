nm_secret_agent_init (NMSecretAgent *self)
{
	NMSecretAgentPrivate *priv = NM_SECRET_AGENT_GET_PRIVATE (self);
	GError *error = NULL;

	priv->bus = dbus_g_bus_get (DBUS_BUS_SYSTEM, &error);
	if (!priv->bus) {
		g_warning ("Couldn't connect to system bus: %s", error->message);
		g_error_free (error);
		return;
	}

	priv->dbus_proxy = dbus_g_proxy_new_for_name (priv->bus,
	                                              DBUS_SERVICE_DBUS,
	                                              DBUS_PATH_DBUS,
	                                              DBUS_INTERFACE_DBUS);
	if (!priv->dbus_proxy) {
		g_warning ("Couldn't create messagebus proxy.");
		return;
	}

	dbus_g_object_register_marshaller (_nm_glib_marshal_VOID__STRING_STRING_STRING,
	                                   G_TYPE_NONE,
	                                   G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING,
	                                   G_TYPE_INVALID);
	dbus_g_proxy_add_signal (priv->dbus_proxy, "NameOwnerChanged",
	                         G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING,
	                         G_TYPE_INVALID);
	dbus_g_proxy_connect_signal (priv->dbus_proxy,
	                             "NameOwnerChanged",
	                             G_CALLBACK (name_owner_changed),
	                             self, NULL);

	priv->manager_proxy = dbus_g_proxy_new_for_name (priv->bus,
	                                                 NM_DBUS_SERVICE,
	                                                 NM_DBUS_PATH_AGENT_MANAGER,
	                                                 NM_DBUS_INTERFACE_AGENT_MANAGER);
	if (!priv->manager_proxy) {
		g_warning ("Couldn't create NM agent manager proxy.");
		return;
	}

	priv->auto_register_id = g_idle_add (auto_register_cb, self);
}
