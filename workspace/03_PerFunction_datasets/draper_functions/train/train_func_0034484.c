camel_network_settings_get_security_method (CamelNetworkSettings *settings)
{
	gpointer data;

	g_return_val_if_fail (
		CAMEL_IS_NETWORK_SETTINGS (settings),
		CAMEL_NETWORK_SECURITY_METHOD_NONE);

	data = g_object_get_data (G_OBJECT (settings), SECURITY_METHOD_KEY);

	return (CamelNetworkSecurityMethod) GPOINTER_TO_INT (data);
}
