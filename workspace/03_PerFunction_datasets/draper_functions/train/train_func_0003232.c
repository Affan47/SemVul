__vpn_manager_init(void)
{
	DBG("");

	connection = connman_dbus_get_connection();
	if (connection == NULL)
		return -1;

	g_dbus_register_interface(connection, VPN_MANAGER_PATH,
					VPN_MANAGER_INTERFACE,
					manager_methods,
					manager_signals, NULL, NULL, NULL);

	vpn_connect_count = 0;

	return 0;
}
