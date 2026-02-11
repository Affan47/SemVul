alua_init(void)
{
	int r;

	kaluad_wq = alloc_workqueue("kaluad", WQ_MEM_RECLAIM, 0);
	if (!kaluad_wq) {

		return SCSI_DH_DEV_TEMP_BUSY;
	}
	kaluad_sync_wq = create_workqueue("kaluad_sync");
	if (!kaluad_sync_wq) {
		destroy_workqueue(kaluad_wq);
		return SCSI_DH_DEV_TEMP_BUSY;
	}
	r = scsi_register_device_handler(&alua_dh);
	if (r != 0) {
		printk(KERN_ERR "%s: Failed to register scsi device handler",
			ALUA_DH_NAME);
		destroy_workqueue(kaluad_sync_wq);
		destroy_workqueue(kaluad_wq);
	}
	return r;
}
