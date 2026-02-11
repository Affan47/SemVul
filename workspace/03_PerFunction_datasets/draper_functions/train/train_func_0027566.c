GMT_lambeq (double lon, double lat, double *x, double *y)
{

	double k, tmp, sin_lat, cos_lat, sin_lon, cos_lon, c;

	GMT_WIND_LON(lon)
	if (project_info.GMT_convert_latitudes) lat = GMT_latg_to_lata (lat);
	sincosd (lat, &sin_lat, &cos_lat);
	sincosd (lon, &sin_lon, &cos_lon);
	c = cos_lat * cos_lon;
	tmp = 1.0 + project_info.sinp * sin_lat + project_info.cosp * c;
	if (tmp > 0.0) {
		k = project_info.EQ_RAD * d_sqrt (2.0 / tmp);
		*x = k * cos_lat * sin_lon;
		*y = k * (project_info.cosp * sin_lat - project_info.sinp * c);
		if (project_info.GMT_convert_latitudes) {
			(*x) *= project_info.Dx;
			(*y) *= project_info.Dy;
		}
	}
	else
		*x = *y = -DBL_MAX;
}
