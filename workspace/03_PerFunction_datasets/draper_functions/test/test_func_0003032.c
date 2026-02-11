ad7793_write_raw(struct iio_dev *indio_dev,
			       struct iio_chan_spec const *chan,
			       int val,
			       int val2,
			       long mask)
{
	struct ad7793_state *st = iio_priv(indio_dev);
	int ret, i;
	unsigned int tmp;

	mutex_lock(&indio_dev->mlock);
	if (iio_buffer_enabled(indio_dev)) {
		mutex_unlock(&indio_dev->mlock);
		return -EBUSY;
	}

	switch (mask) {
	case IIO_CHAN_INFO_SCALE:
		ret = -EINVAL;
		for (i = 0; i < ARRAY_SIZE(st->scale_avail); i++)
			if (val2 == st->scale_avail[i][1]) {
				ret = 0;
				tmp = st->conf;
				st->conf &= ~AD7793_CONF_GAIN(-1);
				st->conf |= AD7793_CONF_GAIN(i);

				if (tmp == st->conf)
					break;

				ad_sd_write_reg(&st->sd, AD7793_REG_CONF,
						sizeof(st->conf), st->conf);
				ad7793_calibrate_all(st);
				break;
			}
		break;
	default:
		ret = -EINVAL;
	}

	mutex_unlock(&indio_dev->mlock);
	return ret;
}
