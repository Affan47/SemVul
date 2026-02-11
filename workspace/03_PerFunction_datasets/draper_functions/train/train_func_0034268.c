apds990x_rate_store(struct device *dev,
				  struct device_attribute *attr,
				  const char *buf, size_t len)
{
	struct apds990x_chip *chip =  dev_get_drvdata(dev);
	unsigned long value;
	int ret;

	ret = kstrtoul(buf, 0, &value);
	if (ret)
		return ret;

	mutex_lock(&chip->mutex);
	ret = apds990x_set_arate(chip, value);
	mutex_unlock(&chip->mutex);

	if (ret < 0)
		return ret;
	return len;
}
