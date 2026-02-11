hfi1_devnode(struct device *dev, umode_t *mode)
{
	if (mode)
		*mode = 0600;
	return kasprintf(GFP_KERNEL, "%s", dev_name(dev));
}
