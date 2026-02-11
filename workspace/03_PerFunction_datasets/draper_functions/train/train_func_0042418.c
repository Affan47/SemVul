show_int_time_available(struct device *dev,
			struct device_attribute *attr, char *buf)
{
	struct iio_dev *indio_dev = dev_to_iio_dev(dev);
	struct isl29018_chip *chip = iio_priv(indio_dev);
	int i, len = 0;

	for (i = 0; i < ARRAY_SIZE(isl29018_int_utimes[chip->type]); ++i)
		len += sprintf(buf + len, "0.%06d ",
			       isl29018_int_utimes[chip->type][i]);

	buf[len - 1] = '\n';

	return len;
}
