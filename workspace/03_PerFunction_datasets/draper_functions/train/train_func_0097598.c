map_log_auto_bound (GogAxis *axis, double minimum, double maximum, double *bound)
{
	double step;

	if (maximum <= 0.0)
		maximum = 1.0;
	if (minimum <= 0.0)
		minimum = maximum / 100.0;
	if (maximum < minimum)
		maximum = minimum * 100.0;

	maximum = go_fake_ceil (log10 (maximum));
	minimum = go_fake_floor (log10 (minimum));

	step = go_fake_ceil ((maximum - minimum + 1.0) /
		     (double) GOG_AXIS_LOG_AUTO_MAX_MAJOR_TICK_NBR);

	bound[GOG_AXIS_ELEM_MIN] = pow (10.0, minimum);
	bound[GOG_AXIS_ELEM_MAX] = pow (10.0, maximum);
	bound[GOG_AXIS_ELEM_MAJOR_TICK] = step;
	bound[GOG_AXIS_ELEM_MINOR_TICK] = 9 * step - 1;
}
