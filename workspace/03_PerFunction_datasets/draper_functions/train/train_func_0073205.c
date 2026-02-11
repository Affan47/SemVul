ad5064_sync_powerdown_mode(struct ad5064_state *st,
	const struct iio_chan_spec *chan)
{
	unsigned int val;
	int ret;

	val = (0x1 << chan->address);

	if (st->pwr_down[chan->channel])
		val |= st->pwr_down_mode[chan->channel] << 8;

	ret = ad5064_write(st, AD5064_CMD_POWERDOWN_DAC, 0, val, 0);

	return ret;
}
