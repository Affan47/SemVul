GMT_albers (double lon, double lat, double *x, double *y)
{


	double s, c, q, theta, rho, r;

	GMT_WIND_LON(lon)

	s = sind (lat);
	if (GMT_IS_ZERO (project_info.ECC))
		q = 2.0 * s;
	else {
		r = project_info.ECC * s;
		q = project_info.one_m_ECC2 * (s / (1.0 - project_info.ECC2 * s * s) - project_info.i_half_ECC * log ((1.0 - r) / (1.0 + r)));
	}
	theta = project_info.a_n * lon * D2R;
	rho = project_info.EQ_RAD * sqrt (project_info.a_C - project_info.a_n * q) * project_info.a_i_n;

	sincos (theta, &s, &c);
	*x = rho * s;
	*y = project_info.a_rho0 - rho * c;
}
