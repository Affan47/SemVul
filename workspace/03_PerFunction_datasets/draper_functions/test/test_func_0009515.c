ad7152_start_calib(struct device *dev,
					 struct device_attribute *attr,
					 const char *buf,
					 size_t len,
					 u8 regval)
{
	struct iio_dev *indio_dev = dev_to_iio_dev(dev);
	struct ad7152_chip_info *chip = iio_priv(indio_dev);
	struct iio_dev_attr *this_attr = to_iio_dev_attr(attr);
	bool doit;
	int ret, timeout = 10;

	ret = strtobool(buf, &doit);
	if (ret < 0)
		return ret;

	if (!doit)
		return 0;

	if (this_attr->address == 0)
		regval |= AD7152_CONF_CH1EN;
	else
		regval |= AD7152_CONF_CH2EN;

	mutex_lock(&indio_dev->mlock);
	ret = i2c_smbus_write_byte_data(chip->client, AD7152_REG_CFG, regval);
	if (ret < 0) {
		mutex_unlock(&indio_dev->mlock);
		return ret;
	}

	do {
		mdelay(20);
		ret = i2c_smbus_read_byte_data(chip->client, AD7152_REG_CFG);
		if (ret < 0) {
			mutex_unlock(&indio_dev->mlock);
			return ret;
		}
	} while ((ret == regval) && timeout--);

	mutex_unlock(&indio_dev->mlock);
	return len;
}
