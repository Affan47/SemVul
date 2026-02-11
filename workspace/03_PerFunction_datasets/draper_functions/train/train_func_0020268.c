set_do_seconds (double inc)
{
	if (GMT_plot_calclock.geo.order[2] == -1) return (FALSE);
	if (GMT_plot_calclock.geo.n_sec_decimals > 0) return (TRUE);
	if (fabs (60.0 * fmod (fmod (inc, 1.0) * 60.0, 1.0)) >= 1.0) return (TRUE);
	return (FALSE);
}
