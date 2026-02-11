cpufv_store(struct device *dev,
			   struct device_attribute *attr,
			   const char *buf, size_t count)
{
	struct eeepc_laptop *eeepc = dev_get_drvdata(dev);
	struct eeepc_cpufv c;
	int rv, value;

	if (eeepc->cpufv_disabled)
		return -EPERM;
	if (get_cpufv(eeepc, &c))
		return -ENODEV;
	rv = parse_arg(buf, &value);
	if (rv < 0)
		return rv;
	if (value < 0 || value >= c.num)
		return -EINVAL;
	rv = set_acpi(eeepc, CM_ASL_CPUFV, value);
	if (rv)
		return rv;
	return count;
}
