dmi_save_ipmi_device(const struct dmi_header *dm)
{
	struct dmi_device *dev;
	void *data;

	data = dmi_alloc(dm->length);
	if (data == NULL)
		return;

	memcpy(data, dm, dm->length);

	dev = dmi_alloc(sizeof(*dev));
	if (!dev)
		return;

	dev->type = DMI_DEV_TYPE_IPMI;
	dev->name = "IPMI controller";
	dev->device_data = data;

	list_add_tail(&dev->list, &dmi_devices);
}
