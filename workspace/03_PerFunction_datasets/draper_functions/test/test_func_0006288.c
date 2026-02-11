ad7816_show_oti(struct device *dev,
			       struct device_attribute *attr,
			       char *buf)
{
	struct iio_dev *indio_dev = dev_to_iio_dev(dev);
	struct ad7816_chip_info *chip = iio_priv(indio_dev);
	int value;

	if (chip->channel_id > AD7816_CS_MAX) {
		dev_err(dev, "Invalid oti channel id %d.\n", chip->channel_id);
		return -EINVAL;
	} else if (chip->channel_id == 0) {
		value = AD7816_BOUND_VALUE_MIN +
			(chip->oti_data[chip->channel_id] -
			AD7816_BOUND_VALUE_BASE);
		return sprintf(buf, "%d\n", value);
	}
	return sprintf(buf, "%u\n", chip->oti_data[chip->channel_id]);
}
