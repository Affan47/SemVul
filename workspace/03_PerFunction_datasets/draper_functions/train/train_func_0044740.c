_drbd_send_uuids(struct drbd_peer_device *peer_device, u64 uuid_flags)
{
	struct drbd_device *device = peer_device->device;
	struct drbd_socket *sock;
	struct p_uuids *p;
	int i;

	if (!get_ldev_if_state(device, D_NEGOTIATING))
		return 0;

	sock = &peer_device->connection->data;
	p = drbd_prepare_command(peer_device, sock);
	if (!p) {
		put_ldev(device);
		return -EIO;
	}
	spin_lock_irq(&device->ldev->md.uuid_lock);
	for (i = UI_CURRENT; i < UI_SIZE; i++)
		p->uuid[i] = cpu_to_be64(device->ldev->md.uuid[i]);
	spin_unlock_irq(&device->ldev->md.uuid_lock);

	device->comm_bm_set = drbd_bm_total_weight(device);
	p->uuid[UI_SIZE] = cpu_to_be64(device->comm_bm_set);
	rcu_read_lock();
	uuid_flags |= rcu_dereference(peer_device->connection->net_conf)->discard_my_data ? 1 : 0;
	rcu_read_unlock();
	uuid_flags |= test_bit(CRASHED_PRIMARY, &device->flags) ? 2 : 0;
	uuid_flags |= device->new_state_tmp.disk == D_INCONSISTENT ? 4 : 0;
	p->uuid[UI_FLAGS] = cpu_to_be64(uuid_flags);

	put_ldev(device);
	return drbd_send_command(peer_device, sock, P_UUIDS, sizeof(*p), NULL, 0);
}
