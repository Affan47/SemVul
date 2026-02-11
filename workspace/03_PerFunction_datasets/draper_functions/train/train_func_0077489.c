nm_vpn_plugin_get_connection (NMVPNPlugin *plugin)
{
	DBusGConnection *connection;

	g_return_val_if_fail (NM_IS_VPN_PLUGIN (plugin), NULL);

	connection = NM_VPN_PLUGIN_GET_PRIVATE (plugin)->connection;

	if (connection)
		dbus_g_connection_ref (connection);

	return connection;
}
