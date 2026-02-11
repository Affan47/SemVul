find_rc_dev(struct device *dev, const void *data)
{
	const struct uwb_dev_addr *addr = data;
	struct uwb_rc *rc = dev_get_drvdata(dev);

	if (rc == NULL) {
		WARN_ON(1);
		return 0;
	}
	if (!uwb_dev_addr_cmp(&rc->uwb_dev.dev_addr, addr)) {
		rc = uwb_rc_get(rc);
		return 1;
	}
	return 0;
}
