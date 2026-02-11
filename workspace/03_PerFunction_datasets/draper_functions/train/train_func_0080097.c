G_begin_geodesic_equation(double lon1, double lat1, double lon2,
			      double lat2)
{
    double sin21, tan1, tan2;

    adjust_lon(&lon1);
    adjust_lon(&lon2);
    adjust_lat(&lat1);
    adjust_lat(&lat2);
    if (lon1 > lon2) {
	register double temp;

	SWAP(lon1, lon2);
	SWAP(lat1, lat2);
    }
    if (lon1 == lon2) {
	A = B = 0.0;
	return 0;
    }
    lon1 = Radians(lon1);
    lon2 = Radians(lon2);
    lat1 = Radians(lat1);
    lat2 = Radians(lat2);

    sin21 = sin(lon2 - lon1);
    tan1 = tan(lat1);
    tan2 = tan(lat2);

    A = (tan2 * cos(lon1) - tan1 * cos(lon2)) / sin21;
    B = (tan2 * sin(lon1) - tan1 * sin(lon2)) / sin21;

    return 1;
}
