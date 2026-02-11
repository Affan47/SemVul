ssd_cleanup_chardev(struct ssd_device *dev)
{
	if (dev->slave) {
		return;
	}

#if (LINUX_VERSION_CODE <= KERNEL_VERSION(2,6,12))
	class_simple_device_remove(MKDEV((dev_t)dev->cmajor, (dev_t)dev->idx));
	devfs_remove("c%s", dev->name);
#elif (LINUX_VERSION_CODE <= KERNEL_VERSION(2,6,14))
	class_device_destroy(ssd_class, MKDEV((dev_t)dev->cmajor, (dev_t)dev->idx));
	devfs_remove("c%s", dev->name);
#elif (LINUX_VERSION_CODE <= KERNEL_VERSION(2,6,17))
	class_device_destroy(ssd_class, MKDEV((dev_t)dev->cmajor, (dev_t)dev->idx));
	devfs_remove("c%s", dev->name);
#elif (LINUX_VERSION_CODE <= KERNEL_VERSION(2,6,24))
	class_device_destroy(ssd_class, MKDEV((dev_t)dev->cmajor, (dev_t)dev->idx));
#else
	device_destroy(ssd_class, MKDEV((dev_t)dev->cmajor, (dev_t)dev->idx));
#endif
}
