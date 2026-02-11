GMT_cassini (double lon, double lat, double *x, double *y)
{


	double tany, N, T, A, C, M, s, c, s2, c2, A2, A3;

	GMT_WIND_LON(lon)
	lon *= D2R;

	if (GMT_IS_ZERO (lat)) {
		*x = project_info.EQ_RAD * lon;
		*y = -project_info.c_M0;
		return;
	}

	lat *= D2R;
	sincos (lat, &s, &c);
	sincos (2.0 * lat, &s2, &c2);
	tany = s / c;
	N = project_info.EQ_RAD / sqrt (1.0 - project_info.ECC2 * s * s);
	T = tany * tany;
	A = lon * c;
	A2 = A * A;
	A3 = A2 * A;
	C = project_info.ECC2 * c * c * project_info.i_one_m_ECC2;
	M = project_info.EQ_RAD * (project_info.c_c1 * lat + s2 * (project_info.c_c2 + c2 * (project_info.c_c3 + c2 * project_info.c_c4)));
	*x = N * (A - T * A3 / 6.0 - (8.0 - T + 8 * C) * T * A3 * A2 / 120.0);
	*y = M - project_info.c_M0 + N * tany * (0.5 * A2 + (5.0 - T + 6.0 * C) * A2 * A2 / 24.0);
}
