ofono_disconnect(DBusConnection *conn, void *user_data)
{
	DBG("");

	if (modem_hash == NULL || context_hash == NULL)
		return;

	g_hash_table_destroy(modem_hash);
	modem_hash = NULL;

	g_hash_table_destroy(context_hash);
	context_hash = NULL;
}
