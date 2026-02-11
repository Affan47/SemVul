devmajorminor_remove_file(struct visor_device *dev, int slot)
{
	int maxdevnodes = ARRAY_SIZE(dev->devnodes) / sizeof(dev->devnodes[0]);
	struct devmajorminor_attribute *myattr = NULL;

	if (slot < 0 || slot >= maxdevnodes)
		return;
	myattr = (struct devmajorminor_attribute *)(dev->devnodes[slot].attr);
	if (!myattr)
		return;
	sysfs_remove_file(&dev->kobjdevmajorminor, &myattr->attr);
	kobject_uevent(&dev->device.kobj, KOBJ_OFFLINE);
	dev->devnodes[slot].attr = NULL;
	kfree(myattr);
}
