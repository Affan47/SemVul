function_show(struct device *dev, struct device_attribute *attr,
		char *buf)
{
	struct dummy	*dum = gadget_dev_to_dummy(dev);

	if (!dum->driver || !dum->driver->function)
		return 0;
	return scnprintf(buf, PAGE_SIZE, "%s\n", dum->driver->function);
}
