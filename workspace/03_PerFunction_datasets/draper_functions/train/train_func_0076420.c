__vpn_provider_cleanup(void)
{
	DBG("");

	g_hash_table_foreach(provider_hash, clean_provider, NULL);

	g_hash_table_destroy(provider_hash);
	provider_hash = NULL;

	connman_agent_driver_unregister(&agent_driver);

	dbus_connection_unref(connection);
}
