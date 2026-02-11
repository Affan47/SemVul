conn_disconnect(struct drbd_connection *connection)
{
	struct drbd_peer_device *peer_device;
	enum drbd_conns oc;
	int vnr;

	if (connection->cstate == C_STANDALONE)
		return;


	conn_request_state(connection, NS(conn, C_NETWORK_FAILURE), CS_HARD);


	drbd_thread_stop(&connection->asender);
	drbd_free_sock(connection);

	rcu_read_lock();
	idr_for_each_entry(&connection->peer_devices, peer_device, vnr) {
		struct drbd_device *device = peer_device->device;
		kref_get(&device->kref);
		rcu_read_unlock();
		drbd_disconnected(peer_device);
		kref_put(&device->kref, drbd_destroy_device);
		rcu_read_lock();
	}
	rcu_read_unlock();

	if (!list_empty(&connection->current_epoch->list))
		drbd_err(connection, "ASSERTION FAILED: connection->current_epoch->list not empty\n");

	atomic_set(&connection->current_epoch->epoch_size, 0);
	connection->send.seen_any_write_yet = false;

	drbd_info(connection, "Connection closed\n");

	if (conn_highest_role(connection) == R_PRIMARY && conn_highest_pdsk(connection) >= D_UNKNOWN)
		conn_try_outdate_peer_async(connection);

	spin_lock_irq(&connection->resource->req_lock);
	oc = connection->cstate;
	if (oc >= C_UNCONNECTED)
		_conn_request_state(connection, NS(conn, C_UNCONNECTED), CS_VERBOSE);

	spin_unlock_irq(&connection->resource->req_lock);

	if (oc == C_DISCONNECTING)
		conn_request_state(connection, NS(conn, C_STANDALONE), CS_VERBOSE | CS_HARD);
}
