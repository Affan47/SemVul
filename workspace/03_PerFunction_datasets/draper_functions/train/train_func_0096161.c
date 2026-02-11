devcd_dev_release(struct device *dev)
{
	struct devcd_entry *devcd = dev_to_devcd(dev);

	devcd->free(devcd->data);
	module_put(devcd->owner);


	if (devcd->failing_dev->kobj.sd)
		sysfs_delete_link(&devcd->failing_dev->kobj, &dev->kobj,
				  "devcoredump");

	put_device(devcd->failing_dev);
	kfree(devcd);
}
