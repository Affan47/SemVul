conn_all_vols_unconf(struct drbd_connection *connection)
{
	struct drbd_peer_device *peer_device;
	bool rv = true;
	int vnr;

	rcu_read_lock();
	idr_for_each_entry(&connection->peer_devices, peer_device, vnr) {
		struct drbd_device *device = peer_device->device;
		if (device->state.disk != D_DISKLESS ||
		    device->state.conn != C_STANDALONE ||
		    device->state.role != R_SECONDARY) {
			rv = false;
			break;
		}
	}
	rcu_read_unlock();

	return rv;
}
