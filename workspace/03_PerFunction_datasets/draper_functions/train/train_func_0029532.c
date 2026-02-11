si476x_radio_range_is_inside_of_the_band(u32 low, u32 high,
							    int band)
{
	return low  >= si476x_bands[band].rangelow &&
		high <= si476x_bands[band].rangehigh;
}
