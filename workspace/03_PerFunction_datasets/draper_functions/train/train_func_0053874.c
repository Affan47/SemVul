ad7606_scan_direct(struct iio_dev *indio_dev, unsigned ch)
{
	struct ad7606_state *st = iio_priv(indio_dev);
	int ret;

	st->done = false;
	gpio_set_value(st->pdata->gpio_convst, 1);

	ret = wait_event_interruptible(st->wq_data_avail, st->done);
	if (ret)
		goto error_ret;

	if (gpio_is_valid(st->pdata->gpio_frstdata)) {
		ret = st->bops->read_block(st->dev, 1, st->data);
		if (ret)
			goto error_ret;
		if (!gpio_get_value(st->pdata->gpio_frstdata)) {

			ad7606_reset(st);
			ret = -EIO;
			goto error_ret;
		}
		ret = st->bops->read_block(st->dev,
			st->chip_info->num_channels - 1, &st->data[1]);
		if (ret)
			goto error_ret;
	} else {
		ret = st->bops->read_block(st->dev,
			st->chip_info->num_channels, st->data);
		if (ret)
			goto error_ret;
	}

	ret = st->data[ch];

error_ret:
	gpio_set_value(st->pdata->gpio_convst, 0);

	return ret;
}
