ican3_sysfs_set_term(struct device *dev,
				    struct device_attribute *attr,
				    const char *buf, size_t count)
{
	struct ican3_dev *mod = netdev_priv(to_net_dev(dev));
	unsigned long enable;
	int ret;

	if (kstrtoul(buf, 0, &enable))
		return -EINVAL;

	ret = ican3_set_termination(mod, enable);
	if (ret)
		return ret;

	return count;
}
