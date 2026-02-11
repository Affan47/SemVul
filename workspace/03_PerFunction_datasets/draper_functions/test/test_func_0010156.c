ad7877_disable_store(struct device *dev,
				     struct device_attribute *attr,
				     const char *buf, size_t count)
{
	struct ad7877 *ts = dev_get_drvdata(dev);
	unsigned int val;
	int error;

	error = kstrtouint(buf, 10, &val);
	if (error)
		return error;

	if (val)
		ad7877_disable(ts);
	else
		ad7877_enable(ts);

	return count;
}
