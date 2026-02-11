finalize (GObject *object)
{
	NMVPNPlugin *plugin = NM_VPN_PLUGIN (object);
	NMVPNPluginPrivate *priv = NM_VPN_PLUGIN_GET_PRIVATE (plugin);

	nm_vpn_plugin_set_connection (plugin, NULL);
	g_free (priv->dbus_service_name);

	if (G_IS_VALUE (&priv->banner))
		g_value_unset (&priv->banner);
	if (G_IS_VALUE (&priv->tundev))
		g_value_unset (&priv->tundev);
	if (G_IS_VALUE (&priv->gateway))
		g_value_unset (&priv->gateway);
	if (G_IS_VALUE (&priv->mtu))
		g_value_unset (&priv->mtu);

	G_OBJECT_CLASS (nm_vpn_plugin_parent_class)->finalize (object);
}
