open_any(struct conf* cf)
{
	int i;
	struct eegdev* dev = NULL;

	for (i=0; prefered_devices[i] != NULL; i++) {
		dev = open_plugin_device(prefered_devices[i], cf);
		if (dev != NULL)
			break;
	}

	if (dev == NULL)
		errno = ENODEV;
	return dev;
}
