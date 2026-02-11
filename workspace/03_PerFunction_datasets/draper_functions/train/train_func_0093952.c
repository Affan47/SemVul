store_vrm_reg(struct device *dev, struct device_attribute *attr,
		const char *buf, size_t count)
{
	struct it87_data *data = dev_get_drvdata(dev);
	unsigned long val;

	if (kstrtoul(buf, 10, &val) < 0)
		return -EINVAL;

	data->vrm = val;

	return count;
}
