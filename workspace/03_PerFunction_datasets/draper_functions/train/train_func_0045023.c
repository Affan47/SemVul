got_BarrierAck(struct drbd_connection *connection, struct packet_info *pi)
{
	struct p_barrier_ack *p = pi->data;
	struct drbd_peer_device *peer_device;
	int vnr;

	tl_release(connection, p->barrier, be32_to_cpu(p->set_size));

	rcu_read_lock();
	idr_for_each_entry(&connection->peer_devices, peer_device, vnr) {
		struct drbd_device *device = peer_device->device;

		if (device->state.conn == C_AHEAD &&
		    atomic_read(&device->ap_in_flight) == 0 &&
		    !test_and_set_bit(AHEAD_TO_SYNC_SOURCE, &device->flags)) {
			device->start_resync_timer.expires = jiffies + HZ;
			add_timer(&device->start_resync_timer);
		}
	}
	rcu_read_unlock();

	return 0;
}
