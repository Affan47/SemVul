ti_bandgap_add_hyst(struct ti_bandgap *bgp, int adc_val, int hyst_val,
			u32 *sum)
{
	int temp, ret;


	ret = ti_bandgap_adc_to_mcelsius(bgp, adc_val, &temp);
	if (ret < 0)
		return ret;

	temp += hyst_val;

	ret = ti_bandgap_mcelsius_to_adc(bgp, temp, sum);
	return ret;
}
