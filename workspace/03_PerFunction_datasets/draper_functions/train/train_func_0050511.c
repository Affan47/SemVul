ad5764_get_channel_vref(struct ad5764_state *st,
	unsigned int channel)
{
	if (st->chip_info->int_vref)
		return st->chip_info->int_vref;
	else
		return regulator_get_voltage(st->vref_reg[channel / 2].consumer);
}
