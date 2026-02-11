ad7877_dac_store(struct device *dev,
				     struct device_attribute *attr,
				     const char *buf, size_t count)
{
	struct ad7877 *ts = dev_get_drvdata(dev);
	unsigned int val;
	int error;

	error = kstrtouint(buf, 10, &val);
	if (error)
		return error;

	mutex_lock(&ts->mutex);
	ts->dac = val & 0xFF;
	ad7877_write(ts->spi, AD7877_REG_DAC, (ts->dac << 4) | AD7877_DAC_CONF);
	mutex_unlock(&ts->mutex);

	return count;
}
