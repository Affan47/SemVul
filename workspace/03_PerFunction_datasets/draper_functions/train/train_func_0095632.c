pi_prot_format_store(struct config_item *item,
		const char *page, size_t count)
{
	struct se_dev_attrib *da = to_attrib(item);
	struct se_device *dev = da->da_dev;
	bool flag;
	int ret;

	ret = strtobool(page, &flag);
	if (ret < 0)
		return ret;

	if (!flag)
		return count;

	if (!dev->transport->format_prot) {
		pr_err("DIF protection format not supported by backend %s\n",
		       dev->transport->name);
		return -ENOSYS;
	}
	if (!(dev->dev_flags & DF_CONFIGURED)) {
		pr_err("DIF protection format requires device to be configured\n");
		return -ENODEV;
	}
	if (dev->export_count) {
		pr_err("dev[%p]: Unable to format SE Device PROT type while"
		       " export_count is %d\n", dev, dev->export_count);
		return -EINVAL;
	}

	ret = dev->transport->format_prot(dev);
	if (ret)
		return ret;

	pr_debug("dev[%p]: SE Device Protection Format complete\n", dev);
	return count;
}
