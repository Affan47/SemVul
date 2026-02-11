read_channel(struct gab *adc_bat, enum power_supply_property psp,
		int *result)
{
	int ret;
	int chan_index;

	chan_index = gab_prop_to_chan(psp);
	ret = iio_read_channel_processed(adc_bat->channel[chan_index],
			result);
	if (ret < 0)
		pr_err("read channel error\n");
	return ret;
}
