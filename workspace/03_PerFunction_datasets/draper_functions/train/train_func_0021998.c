ad9523_write(struct iio_dev *indio_dev, unsigned addr, unsigned val)
{
	struct ad9523_state *st = iio_priv(indio_dev);
	int ret;
	struct spi_transfer t[] = {
		{
			.tx_buf = &st->data[0].d8[2],
			.len = 2,
		}, {
			.tx_buf = &st->data[1].d8[4 - AD9523_TRANSF_LEN(addr)],
			.len = AD9523_TRANSF_LEN(addr),
		},
	};

	st->data[0].d32 = cpu_to_be32(AD9523_WRITE |
				      AD9523_CNT(AD9523_TRANSF_LEN(addr)) |
				      AD9523_ADDR(addr));
	st->data[1].d32 = cpu_to_be32(val);

	ret = spi_sync_transfer(st->spi, t, ARRAY_SIZE(t));

	if (ret < 0)
		dev_err(&indio_dev->dev, "write failed (%d)", ret);

	return ret;
}
