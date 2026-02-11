virtio_dev_match(struct device *_dv, struct device_driver *_dr)
{
	unsigned int i;
	struct virtio_device *dev = dev_to_virtio(_dv);
	const struct virtio_device_id *ids;

	ids = drv_to_virtio(_dr)->id_table;
	for (i = 0; ids[i].device; i++)
		if (virtio_id_match(dev, &ids[i]))
			return 1;
	return 0;
}
