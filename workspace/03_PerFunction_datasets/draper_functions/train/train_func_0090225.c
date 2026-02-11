ib_cache_setup_one(struct ib_device *device)
{
	int p;
	int err;

	rwlock_init(&device->cache.lock);

	device->cache.pkey_cache =
		kzalloc(sizeof *device->cache.pkey_cache *
			(rdma_end_port(device) - rdma_start_port(device) + 1), GFP_KERNEL);
	device->cache.lmc_cache = kmalloc(sizeof *device->cache.lmc_cache *
					  (rdma_end_port(device) -
					   rdma_start_port(device) + 1),
					  GFP_KERNEL);
	if (!device->cache.pkey_cache ||
	    !device->cache.lmc_cache) {
		printk(KERN_WARNING "Couldn't allocate cache "
		       "for %s\n", device->name);
		return -ENOMEM;
	}

	err = gid_table_setup_one(device);
	if (err)

		return err;

	for (p = 0; p <= rdma_end_port(device) - rdma_start_port(device); ++p)
		ib_cache_update(device, p + rdma_start_port(device));

	INIT_IB_EVENT_HANDLER(&device->cache.event_handler,
			      device, ib_cache_event);
	err = ib_register_event_handler(&device->cache.event_handler);
	if (err)
		goto err;

	return 0;

err:
	gid_table_cleanup_one(device);
	return err;
}
