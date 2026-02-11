lp8788_get_vbatt_adc(struct lp8788_charger *pchg, int *result)
{
	struct iio_channel *channel = pchg->chan[LP8788_VBATT];

	if (!channel)
		return -EINVAL;

	return iio_read_channel_processed(channel, result);
}
