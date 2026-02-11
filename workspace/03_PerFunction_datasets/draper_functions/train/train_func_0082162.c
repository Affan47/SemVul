GMT_vcassini (double lon0, double lat0)
{


	double e1, s2, c2;

	GMT_check_R_J (&lon0);
	project_info.central_meridian = lon0;
	project_info.pole = lat0;
	project_info.c_p = lat0 * D2R;
	sincos (2.0 * project_info.c_p, &s2, &c2);

	e1 = (1.0 - d_sqrt (project_info.one_m_ECC2)) / (1.0 + d_sqrt (project_info.one_m_ECC2));

	project_info.c_c1 = 1.0 - (1.0/4.0) * project_info.ECC2 - (3.0/64.0) * project_info.ECC4 - (5.0/256.0) * project_info.ECC6;
	project_info.c_c2 = -((3.0/8.0) * project_info.ECC2 + (3.0/32.0) * project_info.ECC4 + (25.0/768.0) * project_info.ECC6);
	project_info.c_c3 = (15.0/128.0) * project_info.ECC4 + (45.0/512.0) * project_info.ECC6;
	project_info.c_c4 = -(35.0/768.0) * project_info.ECC6;
	project_info.c_M0 = project_info.EQ_RAD * (project_info.c_c1 * project_info.c_p + s2 * (project_info.c_c2 + c2 * (project_info.c_c3 + c2 * project_info.c_c4)));
	project_info.c_i1 = 1.0 / (project_info.EQ_RAD * project_info.c_c1);
	project_info.c_i2 = (3.0/2.0) * e1 - (29.0/12.0) * pow (e1, 3.0);
	project_info.c_i3 = (21.0/8.0) * e1 * e1 - (1537.0/128.0) * pow (e1, 4.0);
	project_info.c_i4 = (151.0/24.0) * pow (e1, 3.0);
	project_info.c_i5 = (1097.0/64.0) * pow (e1, 4.0);
}
