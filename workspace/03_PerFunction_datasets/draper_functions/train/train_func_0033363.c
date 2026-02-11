add_plugin (NMSettings *self, NMSystemConfigInterface *plugin)
{
	NMSettingsPrivate *priv;
	char *pname = NULL;
	char *pinfo = NULL;

	g_return_if_fail (NM_IS_SETTINGS (self));
	g_return_if_fail (NM_IS_SYSTEM_CONFIG_INTERFACE (plugin));

	priv = NM_SETTINGS_GET_PRIVATE (self);

	priv->plugins = g_slist_append (priv->plugins, g_object_ref (plugin));

	g_signal_connect (plugin, NM_SYSTEM_CONFIG_INTERFACE_CONNECTION_ADDED,
	                  G_CALLBACK (plugin_connection_added), self);
	g_signal_connect (plugin, "notify::hostname", G_CALLBACK (hostname_changed), self);

	nm_system_config_interface_init (plugin, NULL);

	g_object_get (G_OBJECT (plugin),
	              NM_SYSTEM_CONFIG_INTERFACE_NAME, &pname,
	              NM_SYSTEM_CONFIG_INTERFACE_INFO, &pinfo,
	              NULL);

	g_signal_connect (plugin, NM_SYSTEM_CONFIG_INTERFACE_UNMANAGED_SPECS_CHANGED,
	                  G_CALLBACK (unmanaged_specs_changed), self);

	nm_log_info (LOGD_SETTINGS, "Loaded plugin %s: %s", pname, pinfo);
	g_free (pname);
	g_free (pinfo);
}
