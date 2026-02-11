show_zone(struct device *dev,
				struct device_attribute *attr, char *buf)
{
	struct iio_dev *indio_dev = dev_to_iio_dev(dev);
	u8 zone;
	int ret;

	ret = lm3533_als_get_zone(indio_dev, &zone);
	if (ret)
		return ret;

	return scnprintf(buf, PAGE_SIZE, "%u\n", zone);
}
