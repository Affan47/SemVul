scsi_debug_exit(void)
{
	int k = scsi_debug_add_host;

	stop_all_queued();
	free_all_queued();
	for (; k; k--)
		sdebug_remove_adapter();
	driver_unregister(&sdebug_driverfs_driver);
	bus_unregister(&pseudo_lld_bus);
	root_device_unregister(pseudo_primary);

	vfree(map_storep);
	vfree(dif_storep);
	vfree(fake_storep);
}
