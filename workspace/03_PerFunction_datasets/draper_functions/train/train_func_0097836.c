GMT_miller (double lon, double lat, double *x, double *y)
{


	GMT_WIND_LON(lon)
	*x = lon * project_info.j_x;
	*y = project_info.j_y * d_log (tand (45.0 + 0.4 * lat));
}
