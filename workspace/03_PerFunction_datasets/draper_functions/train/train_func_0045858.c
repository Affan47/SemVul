camel_network_settings_set_host (CamelNetworkSettings *settings,
                                 const gchar *host)
{
	gchar *stripped_host = NULL;

	g_return_if_fail (CAMEL_IS_NETWORK_SETTINGS (settings));


	if (host == NULL)
		host = "";


	stripped_host = g_strstrip (g_strdup (host));

	G_LOCK (property_lock);

	g_object_set_data_full (
		G_OBJECT (settings),
		HOST_KEY, stripped_host,
		(GDestroyNotify) g_free);

	G_UNLOCK (property_lock);

	g_object_notify (G_OBJECT (settings), "host");
}
