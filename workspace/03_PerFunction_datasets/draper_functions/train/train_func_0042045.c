max1027_read_single_value(struct iio_dev *indio_dev,
				     struct iio_chan_spec const *chan,
				     int *val)
{
	int ret;
	struct max1027_state *st = iio_priv(indio_dev);

	if (iio_buffer_enabled(indio_dev)) {
		dev_warn(&indio_dev->dev, "trigger mode already enabled");
		return -EBUSY;
	}


	st->reg = MAX1027_SETUP_REG | MAX1027_REF_MODE2 | MAX1027_CKS_MODE2;
	ret = spi_write(st->spi, &st->reg, 1);
	if (ret < 0) {
		dev_err(&indio_dev->dev,
			"Failed to configure setup register\n");
		return ret;
	}


	st->reg = MAX1027_CONV_REG | MAX1027_CHAN(chan->channel) |
		  MAX1027_NOSCAN | !!(chan->type == IIO_TEMP);
	ret = spi_write(st->spi, &st->reg, 1);
	if (ret < 0) {
		dev_err(&indio_dev->dev,
			"Failed to configure conversion register\n");
		return ret;
	}


	mdelay(1);


	ret = spi_read(st->spi, st->buffer, (chan->type == IIO_TEMP) ? 4 : 2);
	if (ret < 0)
		return ret;

	*val = be16_to_cpu(st->buffer[0]);

	return IIO_VAL_INT;
}
