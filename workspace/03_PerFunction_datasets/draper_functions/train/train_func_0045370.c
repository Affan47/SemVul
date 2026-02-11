adxl34x_rate_store(struct device *dev,
				  struct device_attribute *attr,
				  const char *buf, size_t count)
{
	struct adxl34x *ac = dev_get_drvdata(dev);
	unsigned char val;
	int error;

	error = kstrtou8(buf, 10, &val);
	if (error)
		return error;

	mutex_lock(&ac->mutex);

	ac->pdata.data_rate = RATE(val);
	AC_WRITE(ac, BW_RATE,
		 ac->pdata.data_rate |
			(ac->pdata.low_power_mode ? LOW_POWER : 0));

	mutex_unlock(&ac->mutex);

	return count;
}
