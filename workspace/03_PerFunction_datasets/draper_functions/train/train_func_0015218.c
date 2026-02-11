bind_mode_store(struct device_driver *drv, const char *buf, size_t count)
{
	struct serio_driver *serio_drv = to_serio_driver(drv);
	int retval;

	retval = count;
	if (!strncmp(buf, "manual", count)) {
		serio_drv->manual_bind = true;
	} else if (!strncmp(buf, "auto", count)) {
		serio_drv->manual_bind = false;
	} else {
		retval = -EINVAL;
	}

	return retval;
}
