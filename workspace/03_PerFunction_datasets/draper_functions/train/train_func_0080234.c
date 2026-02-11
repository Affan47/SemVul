__connman_device_disconnect(struct connman_device *device)
{
	GHashTableIter iter;
	gpointer key, value;

	DBG("device %p", device);

	connman_device_set_disconnected(device, TRUE);

	g_hash_table_iter_init(&iter, device->networks);

	while (g_hash_table_iter_next(&iter, &key, &value) == TRUE) {
		struct connman_network *network = value;

		if (connman_network_get_connecting(network) == TRUE) {


			connman_warn("Skipping disconnect of %s, network is connecting.",
				connman_network_get_identifier(network));
			continue;
		}

		__connman_network_disconnect(network);
	}

	return 0;
}
