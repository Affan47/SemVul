constructor (GType                  type,
             guint                  n_props,
             GObjectConstructParam *props)
{
	GObject *object;
	GeoclueProvider *provider;
	GeoclueProviderPrivate *priv;
	DBusGConnection *connection;
	GError *error = NULL;

	object = G_OBJECT_CLASS (geoclue_provider_parent_class)->constructor
		(type, n_props, props);
	provider = GEOCLUE_PROVIDER (object);
	priv = GET_PRIVATE (provider);

	connection = dbus_g_bus_get (GEOCLUE_DBUS_BUS, &error);
	if (connection == NULL) {
		g_printerr ("Failed to open connection to bus: %s\n",
		            error->message);
		g_error_free (error);
		provider->proxy = NULL;
		priv->geoclue_proxy = NULL;

		return object;
	}


	provider->proxy = dbus_g_proxy_new_for_name (connection,
	                                           priv->service, priv->path,
	                                           priv->interface);


	priv->geoclue_proxy = dbus_g_proxy_new_for_name (connection,
	                                                 priv->service, priv->path,
	                                                 GEOCLUE_INTERFACE_NAME);
	org_freedesktop_Geoclue_add_reference_async (priv->geoclue_proxy,
	                                             add_reference_callback,
	                                             NULL);
	dbus_g_proxy_add_signal (priv->geoclue_proxy, "StatusChanged",
	                         G_TYPE_INT, G_TYPE_INVALID);
	dbus_g_proxy_connect_signal (priv->geoclue_proxy, "StatusChanged",
	                             G_CALLBACK (status_changed),
	                             object, NULL);

	return object;
}
