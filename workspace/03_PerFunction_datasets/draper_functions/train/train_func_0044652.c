dev_get_read_ahead(struct device *dev, uint32_t *read_ahead)
{
	if (!dev)
		return 0;

	if (dev->flags & DEV_REGULAR) {
		*read_ahead = 0;
		return 1;
	}

	return _dev_read_ahead_dev(dev, read_ahead);
}
