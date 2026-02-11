ad7816_store_mode(struct device *dev,
				 struct device_attribute *attr,
				 const char *buf,
				 size_t len)
{
	struct iio_dev *indio_dev = dev_to_iio_dev(dev);
	struct ad7816_chip_info *chip = iio_priv(indio_dev);

	if (strcmp(buf, "full")) {
		gpio_set_value(chip->rdwr_pin, 1);
		chip->mode = AD7816_FULL;
	} else {
		gpio_set_value(chip->rdwr_pin, 0);
		chip->mode = AD7816_PD;
	}

	return len;
}
