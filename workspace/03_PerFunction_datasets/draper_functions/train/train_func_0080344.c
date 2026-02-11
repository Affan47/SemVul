prv_connector_watch_client(const gchar *client_name)
{
	guint watch_id;
	guint *client_id;
	gboolean added = TRUE;

	DLEYNA_LOG_DEBUG("Enter");

	if (g_hash_table_lookup(g_context.clients, client_name)) {
		added = FALSE;
		goto out;
	}

	watch_id = g_bus_watch_name(G_BUS_TYPE_SESSION, client_name,
				      G_BUS_NAME_WATCHER_FLAGS_NONE,
				      NULL, prv_lost_client, NULL,
				      NULL);
	client_id = g_new(guint, 1);
	*client_id = watch_id;
	g_hash_table_insert(g_context.clients, g_strdup(client_name),
			    client_id);

out:
	DLEYNA_LOG_DEBUG("Exit");

	return added;
}
