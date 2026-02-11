GMT_polar (double x, double y, double *x_i, double *y_i)
{
	if (project_info.got_azimuths) x = 90.0 - x;
	if (project_info.got_elevations) y = 90.0 - y;
	sincosd (x - project_info.p_base_angle, y_i, x_i);
	(*x_i) *= y;
	(*y_i) *= y;
}
