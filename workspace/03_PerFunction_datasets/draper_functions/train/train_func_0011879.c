ad7291_write_event_value(struct iio_dev *indio_dev,
				    const struct iio_chan_spec *chan,
				    enum iio_event_type type,
				    enum iio_event_direction dir,
				    enum iio_event_info info,
				    int val, int val2)
{
	struct ad7291_chip_info *chip = iio_priv(indio_dev);

	if (info == IIO_EV_INFO_HYSTERESIS || chan->type == IIO_VOLTAGE) {
		if (val > AD7291_VALUE_MASK || val < 0)
			return -EINVAL;
	} else {
		if (val > 2047 || val < -2048)
			return -EINVAL;
	}

	return ad7291_i2c_write(chip, ad7291_threshold_reg(chan, dir, info),
				val);
}
