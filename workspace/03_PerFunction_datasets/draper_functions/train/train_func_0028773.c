device_detect(const char *name, int type, SANE_Status *status)
{
	struct Magicolor_Scanner *s;
	struct Magicolor_Device *dev;


	for (dev = first_dev; dev; dev = dev->next) {
		if (strcmp(dev->sane.name, name) == 0) {
			dev->missing = 0;
			DBG (10, "%s: Device %s already attached!\n", __func__,
			     name);
			return scanner_create(dev, status);
		}
	}

	if (type == SANE_MAGICOLOR_NODEV) {
		*status = SANE_STATUS_INVAL;
		return NULL;
	}


	dev = malloc(sizeof(*dev));
	if (!dev) {
		*status = SANE_STATUS_NO_MEM;
		return NULL;
	}
	memset(dev, 0x00, sizeof(struct Magicolor_Device));

	s = scanner_create(dev, status);
	if (s == NULL)
		return NULL;

	mc_dev_init(dev, name, type);

	*status = open_scanner(s);
	if (*status != SANE_STATUS_GOOD) {
		free(s);
		return NULL;
	}


	if (dev->connection == SANE_MAGICOLOR_USB) {
		*status = detect_usb(s);
	}

	if (*status != SANE_STATUS_GOOD)
		goto close;


	if (dev->model == NULL)
		mc_set_model(s, "generic", 7);

	dev->name = strdup(name);
	dev->sane.name = dev->name;

	*status = mc_discover_capabilities(s);
	if (*status != SANE_STATUS_GOOD)
		goto close;

	if (source_list[0] == NULL || dev->cap->dpi_range.min == 0) {
		DBG(1, "something is wrong in the discovery process, aborting.\n");
		*status = SANE_STATUS_IO_ERROR;
		goto close;
	}

	mc_dev_post_init(dev);


	num_devices++;
	dev->missing = 0;
	dev->next = first_dev;
	first_dev = dev;

	return s;

	close:
	close_scanner(s);
	free(s);
	return NULL;
}
