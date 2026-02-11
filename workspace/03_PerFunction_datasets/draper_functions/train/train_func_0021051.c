devfreq_cooling_state2power(struct thermal_cooling_device *cdev,
				       struct thermal_zone_device *tz,
				       unsigned long state,
				       u32 *power)
{
	struct devfreq_cooling_device *dfc = cdev->devdata;
	unsigned long freq;
	u32 static_power;

	if (state < 0 || state >= dfc->freq_table_size)
		return -EINVAL;

	freq = dfc->freq_table[state];
	static_power = get_static_power(dfc, freq);

	*power = dfc->power_table[state] + static_power;
	return 0;
}
