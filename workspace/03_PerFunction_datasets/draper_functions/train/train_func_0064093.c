usnic_ib_device_remove(struct usnic_ib_dev *us_ibdev)
{
	usnic_info("Unregistering %s\n", us_ibdev->ib_dev.name);
	usnic_ib_sysfs_unregister_usdev(us_ibdev);
	usnic_fwd_dev_free(us_ibdev->ufdev);
	ib_unregister_device(&us_ibdev->ib_dev);
	ib_dealloc_device(&us_ibdev->ib_dev);
}
