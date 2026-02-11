dmi_save_one_device(int type, const char *name)
{
	struct dmi_device *dev;


	if (dmi_find_device(type, name, NULL))
		return;

	dev = dmi_alloc(sizeof(*dev) + strlen(name) + 1);
	if (!dev)
		return;

	dev->type = type;
	strcpy((char *)(dev + 1), name);
	dev->name = (char *)(dev + 1);
	dev->device_data = NULL;
	list_add(&dev->list, &dmi_devices);
}
