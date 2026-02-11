maki_dbus_emit (makiDBus* d, const gchar* name, GVariant* variant)
{
	g_return_if_fail(d != NULL);

	if (d->connection != NULL)
	{
		g_dbus_connection_emit_signal(d->connection, NULL, SUSHI_DBUS_PATH, SUSHI_DBUS_INTERFACE, name, variant, NULL);
	}
}
