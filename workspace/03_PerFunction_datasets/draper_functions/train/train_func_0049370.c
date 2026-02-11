ad7280_event_handler(int irq, void *private)
{
	struct iio_dev *indio_dev = private;
	struct ad7280_state *st = iio_priv(indio_dev);
	unsigned *channels;
	int i, ret;

	channels = kcalloc(st->scan_cnt, sizeof(*channels), GFP_KERNEL);
	if (!channels)
		return IRQ_HANDLED;

	ret = ad7280_read_all_channels(st, st->scan_cnt, channels);
	if (ret < 0)
		goto out;

	for (i = 0; i < st->scan_cnt; i++) {
		if (((channels[i] >> 23) & 0xF) <= AD7280A_CELL_VOLTAGE_6) {
			if (((channels[i] >> 11) & 0xFFF) >=
				st->cell_threshhigh)
				iio_push_event(indio_dev,
					       IIO_EVENT_CODE(IIO_VOLTAGE,
							1,
							0,
							IIO_EV_DIR_RISING,
							IIO_EV_TYPE_THRESH,
							0, 0, 0),
					       iio_get_time_ns());
			else if (((channels[i] >> 11) & 0xFFF) <=
				st->cell_threshlow)
				iio_push_event(indio_dev,
					       IIO_EVENT_CODE(IIO_VOLTAGE,
							1,
							0,
							IIO_EV_DIR_FALLING,
							IIO_EV_TYPE_THRESH,
							0, 0, 0),
					       iio_get_time_ns());
		} else {
			if (((channels[i] >> 11) & 0xFFF) >= st->aux_threshhigh)
				iio_push_event(indio_dev,
					       IIO_UNMOD_EVENT_CODE(
							IIO_TEMP,
							0,
							IIO_EV_TYPE_THRESH,
							IIO_EV_DIR_RISING),
					       iio_get_time_ns());
			else if (((channels[i] >> 11) & 0xFFF) <=
				st->aux_threshlow)
				iio_push_event(indio_dev,
					       IIO_UNMOD_EVENT_CODE(
							IIO_TEMP,
							0,
							IIO_EV_TYPE_THRESH,
							IIO_EV_DIR_FALLING),
					       iio_get_time_ns());
		}
	}

out:
	kfree(channels);

	return IRQ_HANDLED;
}
