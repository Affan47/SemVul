load_connections (NMSettings *self)
{
	NMSettingsPrivate *priv = NM_SETTINGS_GET_PRIVATE (self);
	GSList *iter;

	if (priv->connections_loaded)
		return;

	for (iter = priv->plugins; iter; iter = g_slist_next (iter)) {
		NMSystemConfigInterface *plugin = NM_SYSTEM_CONFIG_INTERFACE (iter->data);
		GSList *plugin_connections;
		GSList *elt;

		plugin_connections = nm_system_config_interface_get_connections (plugin);


		for (elt = plugin_connections; elt; elt = g_slist_next (elt))
			claim_connection (self, NM_SETTINGS_CONNECTION (elt->data), TRUE);

		g_slist_free (plugin_connections);
	}

	priv->connections_loaded = TRUE;


	unmanaged_specs_changed (NULL, self);

	g_signal_emit (self, signals[CONNECTIONS_LOADED], 0);
	g_signal_emit_by_name (self, NM_CP_SIGNAL_CONNECTIONS_LOADED);
}
