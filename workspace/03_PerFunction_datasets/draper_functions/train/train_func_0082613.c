test_get_active_connections (NMClient *client)
{
	const GPtrArray *connections;
	int i;

	g_print ("Active connections:\n");
	connections = nm_client_get_active_connections (client);
	for (i = 0; connections && (i < connections->len); i++) {
		const GPtrArray *devices;

		g_print ("    %s\n", nm_object_get_path (g_ptr_array_index (connections, i)));
		devices = nm_active_connection_get_devices (g_ptr_array_index (connections, i));
		if (devices)
			g_ptr_array_foreach ((GPtrArray *) devices, show_active_connection_device, NULL);
	}
}
