bmc150_accel_read_raw(struct iio_dev *indio_dev,
				 struct iio_chan_spec const *chan,
				 int *val, int *val2, long mask)
{
	struct bmc150_accel_data *data = iio_priv(indio_dev);
	int ret;

	switch (mask) {
	case IIO_CHAN_INFO_RAW:
		switch (chan->type) {
		case IIO_TEMP:
			return bmc150_accel_get_temp(data, val);
		case IIO_ACCEL:
			if (iio_buffer_enabled(indio_dev))
				return -EBUSY;
			else
				return bmc150_accel_get_axis(data, chan, val);
		default:
			return -EINVAL;
		}
	case IIO_CHAN_INFO_OFFSET:
		if (chan->type == IIO_TEMP) {
			*val = BMC150_ACCEL_TEMP_CENTER_VAL;
			return IIO_VAL_INT;
		} else {
			return -EINVAL;
		}
	case IIO_CHAN_INFO_SCALE:
		*val = 0;
		switch (chan->type) {
		case IIO_TEMP:
			*val2 = 500000;
			return IIO_VAL_INT_PLUS_MICRO;
		case IIO_ACCEL:
		{
			int i;
			const struct bmc150_scale_info *si;
			int st_size = ARRAY_SIZE(data->chip_info->scale_table);

			for (i = 0; i < st_size; ++i) {
				si = &data->chip_info->scale_table[i];
				if (si->reg_range == data->range) {
					*val2 = si->scale;
					return IIO_VAL_INT_PLUS_MICRO;
				}
			}
			return -EINVAL;
		}
		default:
			return -EINVAL;
		}
	case IIO_CHAN_INFO_SAMP_FREQ:
		mutex_lock(&data->mutex);
		ret = bmc150_accel_get_bw(data, val, val2);
		mutex_unlock(&data->mutex);
		return ret;
	default:
		return -EINVAL;
	}
}
