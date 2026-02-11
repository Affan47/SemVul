dig_find_intersection(double ax1, double ay1,
		      double ax2, double ay2,
		      double bx1, double by1,
		      double bx2, double by2, double *x, double *y)
{
    register double d, r1, r2;
    double t;

    d = D;

    if (d) {

	r1 = D1 / d;
	r2 = D2 / d;
	if (r1 < 0 || r1 > 1 || r2 < 0 || r2 > 1) {
	    return 0;
	}
	*x = ax1 + r1 * (ax2 - ax1);
	*y = ay1 + r1 * (ay2 - ay1);
	return 1;
    }


    if (D1 || D2) {
	return 0;
    }


    if (ax1 > ax2) {
	t = ax1;
	ax1 = ax2;
	ax2 = t;
    }
    if (bx1 > bx2) {
	t = bx1;
	bx1 = bx2;
	bx2 = t;
    }
    if (ax1 > bx2)
	return 0;
    if (ax2 < bx1)
	return 0;


    if (ax1 == bx2) {
	*x = ax1;
	*y = ay1;
	return 1;
    }
    if (ax2 == bx1) {
	*x = ax2;
	*y = ay2;
	return 1;
    }
    return -1;
}
