raid5_store_rmw_level(struct mddev  *mddev, const char *page, size_t len)
{
	struct r5conf *conf = mddev->private;
	unsigned long new;

	if (!conf)
		return -ENODEV;

	if (len >= PAGE_SIZE)
		return -EINVAL;

	if (kstrtoul(page, 10, &new))
		return -EINVAL;

	if (new != PARITY_DISABLE_RMW && !raid6_call.xor_syndrome)
		return -EINVAL;

	if (new != PARITY_DISABLE_RMW &&
	    new != PARITY_ENABLE_RMW &&
	    new != PARITY_PREFER_RMW)
		return -EINVAL;

	conf->rmw_level = new;
	return len;
}
