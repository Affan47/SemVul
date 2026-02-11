adxrs450_spi_sensor_data(struct iio_dev *indio_dev, s16 *val)
{
	struct adxrs450_state *st = iio_priv(indio_dev);
	int ret;
	struct spi_transfer xfers[] = {
		{
			.tx_buf = &st->tx,
			.bits_per_word = 8,
			.len = sizeof(st->tx),
			.cs_change = 1,
		}, {
			.rx_buf = &st->rx,
			.bits_per_word = 8,
			.len = sizeof(st->rx),
		},
	};

	mutex_lock(&st->buf_lock);
	st->tx = cpu_to_be32(ADXRS450_SENSOR_DATA);

	ret = spi_sync_transfer(st->us, xfers, ARRAY_SIZE(xfers));
	if (ret) {
		dev_err(&st->us->dev, "Problem while reading sensor data\n");
		goto error_ret;
	}

	*val = (be32_to_cpu(st->rx) >> 10) & 0xFFFF;

error_ret:
	mutex_unlock(&st->buf_lock);
	return ret;
}
