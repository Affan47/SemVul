sx9500_trigger_handler(int irq, void *private)
{
	struct iio_poll_func *pf = private;
	struct iio_dev *indio_dev = pf->indio_dev;
	struct sx9500_data *data = iio_priv(indio_dev);
	int val, bit, ret, i = 0;

	mutex_lock(&data->mutex);

	for_each_set_bit(bit, indio_dev->active_scan_mask,
			 indio_dev->masklength) {
		ret = sx9500_read_prox_data(data, &indio_dev->channels[bit],
					    &val);
		if (ret < 0)
			goto out;

		data->buffer[i++] = val;
	}

	iio_push_to_buffers_with_timestamp(indio_dev, data->buffer,
					   iio_get_time_ns());

out:
	mutex_unlock(&data->mutex);

	iio_trigger_notify_done(indio_dev->trig);

	return IRQ_HANDLED;
}
