rebind_store(struct device_driver *dev, const char *buf,
				 size_t count)
{
	int ret;
	int len;
	struct bus_id_priv *bid;


	len = strnlen(buf, BUSID_SIZE);

	if (!(len < BUSID_SIZE))
		return -EINVAL;

	bid = get_busid_priv(buf);
	if (!bid)
		return -ENODEV;

	ret = device_attach(&bid->udev->dev);
	if (ret < 0) {
		dev_err(&bid->udev->dev, "rebind failed\n");
		return ret;
	}

	return count;
}
