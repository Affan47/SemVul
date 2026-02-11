iser_init(void)
{
	int err;

	iser_dbg("Starting iSER datamover...\n");

	if (iscsi_max_lun < 1) {
		iser_err("Invalid max_lun value of %u\n", iscsi_max_lun);
		return -EINVAL;
	}

	memset(&ig, 0, sizeof(struct iser_global));

	ig.desc_cache = kmem_cache_create("iser_descriptors",
					  sizeof(struct iser_tx_desc),
					  0, SLAB_HWCACHE_ALIGN,
					  NULL);
	if (ig.desc_cache == NULL)
		return -ENOMEM;


	mutex_init(&ig.device_list_mutex);
	INIT_LIST_HEAD(&ig.device_list);
	mutex_init(&ig.connlist_mutex);
	INIT_LIST_HEAD(&ig.connlist);

	release_wq = alloc_workqueue("release workqueue", 0, 0);
	if (!release_wq) {
		iser_err("failed to allocate release workqueue\n");
		return -ENOMEM;
	}

	iscsi_iser_scsi_transport = iscsi_register_transport(
							&iscsi_iser_transport);
	if (!iscsi_iser_scsi_transport) {
		iser_err("iscsi_register_transport failed\n");
		err = -EINVAL;
		goto register_transport_failure;
	}

	return 0;

register_transport_failure:
	kmem_cache_destroy(ig.desc_cache);

	return err;
}
