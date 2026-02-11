clients_init (void)
{
	GError *error = NULL;
	connection = g_bus_get_sync (G_BUS_TYPE_SESSION, NULL, &error);

	if (error) {
		g_critical ("Could not connect to the D-Bus session bus, %s",
		            error ? error->message : "no error given.");
		g_clear_error (&error);
		connection = NULL;
	}

	clients = g_hash_table_new_full (g_str_hash,
	                                 g_str_equal,
	                                 NULL,
	                                 client_data_free);

	return TRUE;
}
