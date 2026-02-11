tsl2563_read_thresh(struct iio_dev *indio_dev,
	const struct iio_chan_spec *chan, enum iio_event_type type,
	enum iio_event_direction dir, enum iio_event_info info, int *val,
	int *val2)
{
	struct tsl2563_chip *chip = iio_priv(indio_dev);

	switch (dir) {
	case IIO_EV_DIR_RISING:
		*val = chip->high_thres;
		break;
	case IIO_EV_DIR_FALLING:
		*val = chip->low_thres;
		break;
	default:
		return -EINVAL;
	}

	return IIO_VAL_INT;
}
