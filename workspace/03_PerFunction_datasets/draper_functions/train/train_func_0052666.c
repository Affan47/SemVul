mcp320x_read_raw(struct iio_dev *indio_dev,
			    struct iio_chan_spec const *channel, int *val,
			    int *val2, long mask)
{
	struct mcp320x *adc = iio_priv(indio_dev);
	int ret = -EINVAL;
	int device_index = 0;

	mutex_lock(&adc->lock);

	device_index = spi_get_device_id(adc->spi)->driver_data;

	switch (mask) {
	case IIO_CHAN_INFO_RAW:
		ret = mcp320x_adc_conversion(adc, channel->address,
			channel->differential, device_index, val);
		if (ret < 0)
			goto out;

		ret = IIO_VAL_INT;
		break;

	case IIO_CHAN_INFO_SCALE:
		ret = regulator_get_voltage(adc->reg);
		if (ret < 0)
			goto out;


		*val = ret / 1000;
		*val2 = adc->chip_info->resolution;
		ret = IIO_VAL_FRACTIONAL_LOG2;
		break;
	}

out:
	mutex_unlock(&adc->lock);

	return ret;
}
