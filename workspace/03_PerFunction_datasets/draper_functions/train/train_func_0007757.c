bcm_device_exists(struct bcm_device *device)
{
	struct list_head *p;

	list_for_each(p, &bcm_device_list) {
		struct bcm_device *dev = list_entry(p, struct bcm_device, list);

		if (device == dev)
			return true;
	}

	return false;
}
