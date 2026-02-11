obs_current_hour_angle(struct obs_data *obs)
{
	double jd, ha;
	struct timeval tv;

	gettimeofday(&tv, NULL);
	jd = timeval_to_jdate(&tv);

	ha = get_apparent_sidereal_time(jd) - (P_DBL(OBS_LONGITUDE) + obs->ra) / 15.0;
	if (ha > 12)
		ha -= 24;
	d3_printf("current ha = %f\n", ha);
	return ha;
}
