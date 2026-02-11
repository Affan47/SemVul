ad5764_read(struct iio_dev *indio_dev, unsigned int reg,
	unsigned int *val)
{
	struct ad5764_state *st = iio_priv(indio_dev);
	int ret;
	struct spi_transfer t[] = {
		{
			.tx_buf = &st->data[0].d8[1],
			.len = 3,
			.cs_change = 1,
		}, {
			.rx_buf = &st->data[1].d8[1],
			.len = 3,
		},
	};

	mutex_lock(&indio_dev->mlock);

	st->data[0].d32 = cpu_to_be32((1 << 23) | (reg << 16));

	ret = spi_sync_transfer(st->spi, t, ARRAY_SIZE(t));
	if (ret >= 0)
		*val = be32_to_cpu(st->data[1].d32) & 0xffff;

	mutex_unlock(&indio_dev->mlock);

	return ret;
}
