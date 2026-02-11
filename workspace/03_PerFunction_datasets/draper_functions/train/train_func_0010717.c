connection_unregister(const char *path, uint16_t id)
{
	struct network_peer *peer;
	struct network_conn *nc;

	peer = find_peer(peers, path);
	if (!peer)
		return;

	nc = find_connection(peer->connections, id);
	if (!nc)
		return;

	peer->connections = g_slist_remove(peer->connections, nc);
	connection_free(nc);
	if (peer->connections)
		return;

	g_dbus_unregister_interface(connection, path, NETWORK_PEER_INTERFACE);
}
