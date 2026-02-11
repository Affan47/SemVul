show_thresh_either_en(struct device *dev,
					struct device_attribute *attr,
					char *buf)
{
	struct iio_dev *indio_dev = dev_to_iio_dev(dev);
	struct lm3533_als *als = iio_priv(indio_dev);
	int enable;
	int ret;

	if (als->irq) {
		ret = lm3533_als_get_int_mode(indio_dev, &enable);
		if (ret)
			return ret;
	} else {
		enable = 0;
	}

	return scnprintf(buf, PAGE_SIZE, "%u\n", enable);
}
