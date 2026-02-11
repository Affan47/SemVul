nau7802_write_raw(struct iio_dev *indio_dev,
			     struct iio_chan_spec const *chan,
			     int val, int val2, long mask)
{
	struct nau7802_state *st = iio_priv(indio_dev);
	int i, ret;

	switch (mask) {
	case IIO_CHAN_INFO_SCALE:
		for (i = 0; i < ARRAY_SIZE(st->scale_avail); i++)
			if (val2 == st->scale_avail[i])
				return nau7802_set_gain(st, i);

		break;

	case IIO_CHAN_INFO_SAMP_FREQ:
		for (i = 0; i < ARRAY_SIZE(nau7802_sample_freq_avail); i++)
			if (val == nau7802_sample_freq_avail[i]) {
				mutex_lock(&st->lock);
				st->sample_rate = i;
				st->conversion_count = 0;
				ret = i2c_smbus_write_byte_data(st->client,
					NAU7802_REG_CTRL2,
					NAU7802_CTRL2_CRS(st->sample_rate));
				mutex_unlock(&st->lock);
				return ret;
			}

		break;

	default:
		break;
	}

	return -EINVAL;
}
