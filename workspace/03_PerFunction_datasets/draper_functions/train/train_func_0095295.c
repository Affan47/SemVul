bh1750_read_raw(struct iio_dev *indio_dev,
			   struct iio_chan_spec const *chan,
			   int *val, int *val2, long mask)
{
	int ret, tmp;
	struct bh1750_data *data = iio_priv(indio_dev);
	const struct bh1750_chip_info *chip_info = data->chip_info;

	switch (mask) {
	case IIO_CHAN_INFO_RAW:
		switch (chan->type) {
		case IIO_LIGHT:
			mutex_lock(&data->lock);
			ret = bh1750_read(data, val);
			mutex_unlock(&data->lock);
			if (ret < 0)
				return ret;

			return IIO_VAL_INT;
		default:
			return -EINVAL;
		}
	case IIO_CHAN_INFO_SCALE:
		tmp = chip_info->mtreg_to_scale / data->mtreg;
		*val = tmp / 1000000;
		*val2 = tmp % 1000000;
		return IIO_VAL_INT_PLUS_MICRO;
	case IIO_CHAN_INFO_INT_TIME:
		*val = 0;
		*val2 = chip_info->mtreg_to_usec * data->mtreg;
		return IIO_VAL_INT_PLUS_MICRO;
	default:
		return -EINVAL;
	}
}
