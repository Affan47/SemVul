iio_channel_read(struct iio_channel *chan, int *val, int *val2,
	enum iio_chan_info_enum info)
{
	int unused;
	int vals[INDIO_MAX_RAW_ELEMENTS];
	int ret;
	int val_len = 2;

	if (val2 == NULL)
		val2 = &unused;

	if(!iio_channel_has_info(chan->channel, info))
		return -EINVAL;

	if (chan->indio_dev->info->read_raw_multi) {
		ret = chan->indio_dev->info->read_raw_multi(chan->indio_dev,
					chan->channel, INDIO_MAX_RAW_ELEMENTS,
					vals, &val_len, info);
		*val = vals[0];
		*val2 = vals[1];
	} else
		ret = chan->indio_dev->info->read_raw(chan->indio_dev,
					chan->channel, val, val2, info);

	return ret;
}
