histogram_toggle_mode(Histogram *histogram)
{
	if (!histogram) return 0;
	return histogram_set_mode(histogram, !histogram_get_mode(histogram));
}
