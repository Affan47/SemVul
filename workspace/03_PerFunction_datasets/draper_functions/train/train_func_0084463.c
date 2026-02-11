set_oversampling(struct device *dev,
				struct device_attribute *attr,
				const char *buf, size_t count)
{
	struct bmp085_data *data = dev_get_drvdata(dev);
	unsigned long oversampling;
	int err = kstrtoul(buf, 10, &oversampling);

	if (err == 0) {
		mutex_lock(&data->lock);
		bmp085_set_oversampling(data, oversampling);
		mutex_unlock(&data->lock);
		return count;
	}

	return err;
}
