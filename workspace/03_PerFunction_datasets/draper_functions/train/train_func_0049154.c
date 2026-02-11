ad5504_write_dac_powerdown(struct iio_dev *indio_dev,
	uintptr_t private, const struct iio_chan_spec *chan, const char *buf,
	size_t len)
{
	bool pwr_down;
	int ret;
	struct ad5504_state *st = iio_priv(indio_dev);

	ret = strtobool(buf, &pwr_down);
	if (ret)
		return ret;

	if (pwr_down)
		st->pwr_down_mask |= (1 << chan->channel);
	else
		st->pwr_down_mask &= ~(1 << chan->channel);

	ret = ad5504_spi_write(st, AD5504_ADDR_CTRL,
				AD5504_DAC_PWRDWN_MODE(st->pwr_down_mode) |
				AD5504_DAC_PWR(st->pwr_down_mask));


	ad5504_spi_write(st, AD5504_ADDR_NOOP, 0);

	return ret ? ret : len;
}
