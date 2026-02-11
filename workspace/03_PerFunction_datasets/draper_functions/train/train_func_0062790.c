connection_free(void *data)
{
	struct network_conn *nc = data;

	if (nc->dc_id)
		device_remove_disconnect_watch(nc->peer->device, nc->dc_id);

	connection_destroy(connection, nc);

	g_free(nc);
	nc = NULL;
}
