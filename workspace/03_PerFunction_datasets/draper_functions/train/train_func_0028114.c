ad5764_read_raw(struct iio_dev *indio_dev,
	struct iio_chan_spec const *chan, int *val, int *val2, long info)
{
	struct ad5764_state *st = iio_priv(indio_dev);
	unsigned int reg;
	int vref;
	int ret;

	switch (info) {
	case IIO_CHAN_INFO_RAW:
		reg = AD5764_REG_DATA(chan->address);
		ret = ad5764_read(indio_dev, reg, val);
		if (ret < 0)
			return ret;
		*val >>= chan->scan_type.shift;
		return IIO_VAL_INT;
	case IIO_CHAN_INFO_CALIBBIAS:
		reg = AD5764_REG_OFFSET(chan->address);
		ret = ad5764_read(indio_dev, reg, val);
		if (ret < 0)
			return ret;
		*val = sign_extend32(*val, 7);
		return IIO_VAL_INT;
	case IIO_CHAN_INFO_CALIBSCALE:
		reg = AD5764_REG_FINE_GAIN(chan->address);
		ret = ad5764_read(indio_dev, reg, val);
		if (ret < 0)
			return ret;
		*val = sign_extend32(*val, 5);
		return IIO_VAL_INT;
	case IIO_CHAN_INFO_SCALE:

		vref = ad5764_get_channel_vref(st, chan->channel);
		if (vref < 0)
			return vref;

		*val = vref * 4 / 1000;
		*val2 = chan->scan_type.realbits;
		return IIO_VAL_FRACTIONAL_LOG2;
	case IIO_CHAN_INFO_OFFSET:
		*val = -(1 << chan->scan_type.realbits) / 2;
		return IIO_VAL_INT;
	}

	return -EINVAL;
}
