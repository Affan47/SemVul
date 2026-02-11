GMT_radial_crossing (double lon1, double lat1, double lon2, double lat2, double *clon, double *clat, double *xx, double *yy, GMT_LONG *sides)
{


	double dist1, dist2, delta, eps, dlon;

	dist1 = GMT_great_circle_dist (project_info.central_meridian, project_info.pole, lon1, lat1);
	dist2 = GMT_great_circle_dist (project_info.central_meridian, project_info.pole, lon2, lat2);
	delta = dist2 - dist1;
	eps = (GMT_IS_ZERO (delta)) ? 0.0 : (project_info.f_horizon - dist1) / delta;
	dlon = lon2 - lon1;
	if (fabs (dlon) > 180.0) dlon = copysign (360.0 - fabs (dlon), -dlon);
	clon[0] = lon1 + dlon * eps;
	clat[0] = lat1 + (lat2 - lat1) * eps;

	GMT_geo_to_xy (clon[0], clat[0], &xx[0], &yy[0]);

	sides[0] = 1;

	return (1);
}
