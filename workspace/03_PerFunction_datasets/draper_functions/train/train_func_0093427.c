ad7887_read_raw(struct iio_dev *indio_dev,
			   struct iio_chan_spec const *chan,
			   int *val,
			   int *val2,
			   long m)
{
	int ret;
	struct ad7887_state *st = iio_priv(indio_dev);

	switch (m) {
	case IIO_CHAN_INFO_RAW:
		mutex_lock(&indio_dev->mlock);
		if (iio_buffer_enabled(indio_dev))
			ret = -EBUSY;
		else
			ret = ad7887_scan_direct(st, chan->address);
		mutex_unlock(&indio_dev->mlock);

		if (ret < 0)
			return ret;
		*val = ret >> chan->scan_type.shift;
		*val &= GENMASK(chan->scan_type.realbits - 1, 0);
		return IIO_VAL_INT;
	case IIO_CHAN_INFO_SCALE:
		if (st->reg) {
			*val = regulator_get_voltage(st->reg);
			if (*val < 0)
				return *val;
			*val /= 1000;
		} else {
			*val = st->chip_info->int_vref_mv;
		}

		*val2 = chan->scan_type.realbits;

		return IIO_VAL_FRACTIONAL_LOG2;
	}
	return -EINVAL;
}
