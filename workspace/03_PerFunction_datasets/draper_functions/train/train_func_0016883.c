drbd_alloc_pages(struct drbd_peer_device *peer_device, unsigned int number,
			      bool retry)
{
	struct drbd_device *device = peer_device->device;
	struct page *page = NULL;
	struct net_conf *nc;
	DEFINE_WAIT(wait);
	unsigned int mxb;

	rcu_read_lock();
	nc = rcu_dereference(peer_device->connection->net_conf);
	mxb = nc ? nc->max_buffers : 1000000;
	rcu_read_unlock();

	if (atomic_read(&device->pp_in_use) < mxb)
		page = __drbd_alloc_pages(device, number);

	while (page == NULL) {
		prepare_to_wait(&drbd_pp_wait, &wait, TASK_INTERRUPTIBLE);

		drbd_kick_lo_and_reclaim_net(device);

		if (atomic_read(&device->pp_in_use) < mxb) {
			page = __drbd_alloc_pages(device, number);
			if (page)
				break;
		}

		if (!retry)
			break;

		if (signal_pending(current)) {
			drbd_warn(device, "drbd_alloc_pages interrupted!\n");
			break;
		}

		if (schedule_timeout(HZ/10) == 0)
			mxb = UINT_MAX;
	}
	finish_wait(&drbd_pp_wait, &wait);

	if (page)
		atomic_add(number, &device->pp_in_use);
	return page;
}
