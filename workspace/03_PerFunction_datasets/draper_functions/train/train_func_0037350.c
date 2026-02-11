hdc100x_write_raw(struct iio_dev *indio_dev,
			     struct iio_chan_spec const *chan,
			     int val, int val2, long mask)
{
	struct hdc100x_data *data = iio_priv(indio_dev);
	int ret = -EINVAL;

	switch (mask) {
	case IIO_CHAN_INFO_INT_TIME:
		if (val != 0)
			return -EINVAL;

		mutex_lock(&data->lock);
		ret = hdc100x_set_it_time(data, chan->address, val2);
		mutex_unlock(&data->lock);
		return ret;
	case IIO_CHAN_INFO_RAW:
		if (chan->type != IIO_CURRENT || val2 != 0)
			return -EINVAL;

		mutex_lock(&data->lock);
		ret = hdc100x_update_config(data, HDC100X_REG_CONFIG_HEATER_EN,
					val ? HDC100X_REG_CONFIG_HEATER_EN : 0);
		mutex_unlock(&data->lock);
		return ret;
	default:
		return -EINVAL;
	}
}
