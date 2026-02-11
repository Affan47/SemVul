otg_mode_show(struct device *device,
			     struct device_attribute *attr, char *buf)
{
	struct tahvo_usb *tu = dev_get_drvdata(device);

	switch (tu->tahvo_mode) {
	case TAHVO_MODE_HOST:
		return sprintf(buf, "host\n");
	case TAHVO_MODE_PERIPHERAL:
		return sprintf(buf, "peripheral\n");
	}

	return -EINVAL;
}
