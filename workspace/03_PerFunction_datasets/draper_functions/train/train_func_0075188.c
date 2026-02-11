GMT_plot_ellipse (double lon, double lat, double z, double major, double minor, double azimuth, struct GMT_FILL fill, GMT_LONG outline)
{


	GMT_LONG i;
	double delta_azimuth, sin_azimuth, cos_azimuth, sinp, cosp, angle, x, y, x_prime, y_prime, rho, c;
	double sin_c, cos_c, center, *px = NULL, *py = NULL;

	(void)GMT_alloc_memory2 ((void **)&px, (void **)&py, GMT_ELLIPSE_APPROX+1, 0, sizeof (double), GMT_program);

	delta_azimuth = 2.0 * M_PI / GMT_ELLIPSE_APPROX;
	major *= 500.0;	minor *= 500.0;
	sincosd (90.0 - azimuth, &sin_azimuth, &cos_azimuth);
	sincosd (lat, &sinp, &cosp);

	center = (project_info.central_meridian < project_info.w || project_info.central_meridian > project_info.e) ? 0.5 * (project_info.w + project_info.e) :  project_info.central_meridian;


	for (i = 0; i < GMT_ELLIPSE_APPROX; i++) {

		angle = i * delta_azimuth;

		sincos (angle, &y, &x);
		x *= major;
		y *= minor;


		x_prime = x * cos_azimuth - y * sin_azimuth;
		y_prime = x * sin_azimuth + y * cos_azimuth;


		rho = hypot (x_prime, y_prime);

		c = rho / project_info.EQ_RAD;
		sincos (c, &sin_c, &cos_c);
		py[i] = d_asind (cos_c * sinp + (y_prime * sin_c * cosp / rho));
		if ((lat - 90.0) > -GMT_CONV_LIMIT)
			px[i] = lon + d_atan2d (x_prime, -y_prime);
		else if ((lat + 90.0) < GMT_CONV_LIMIT)
			px[i] = lon + d_atan2d (x_prime, y_prime);
		else
			px[i] = lon + d_atan2d (x_prime * sin_c, (rho * cosp * cos_c - y_prime * sinp * sin_c));
		while ((px[i] - center) < -180.0) px[i] += 360.0;
		while ((px[i] - center) > +180.0) px[i] -= 360.0;
	}

	px[GMT_ELLIPSE_APPROX] = px[0];	py[GMT_ELLIPSE_APPROX] = py[0];
	GMT_fill_polygon (px, py, z, (GMT_LONG)(GMT_ELLIPSE_APPROX+1), &fill, outline);

	GMT_free ((void *)px);
	GMT_free ((void *)py);
}
