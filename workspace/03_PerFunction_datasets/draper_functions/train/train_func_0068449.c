GMT_erfinv (double y)
{
	double x = 0.0, fy, z;


	static double a[4] = {0.886226899, -1.645349621,  0.914624893, -0.140543331};
	static double b[4] = {-2.118377725, 1.442710462, -0.329097515, 0.012229801};
	static double c[4] = {-1.970840454, -1.624906493, 3.429567803, 1.641345311};
	static double d[2] = {3.543889200, 1.637067800};

	fy = fabs (y);

	if (fy > 1.0) return (GMT_d_NaN);

	if (GMT_IS_ZERO (1.0 - fy)) {
		return (copysign (DBL_MAX, y));
	}

	if (y > 0.7) {
		z = sqrt (-log (0.5 * (1.0 - y)));
		x = (((c[3] * z + c[2]) * z + c[1]) * z + c[0]) / ((d[1] * z + d[0]) * z + 1.0);
	}
	else if (y < -0.7) {
		z = sqrt (-log (0.5 * (1.0 + y)));
		x = -(((c[3] * z + c[2]) * z + c[1]) * z + c[0]) / ((d[1] * z + d[0]) * z + 1.0);
	}
	else {
		z = y * y;
		x = y * (((a[3] * z + a[2]) * z + a[1]) * z + a[0]) / ((((b[3] * z + b[2]) * z + b[1]) * z + b[0]) * z + 1.0);
	}


	x -= (erf (x) - y) / (M_2_SQRTPI * exp (-x * x));
	x -= (erf (x) - y) / (M_2_SQRTPI * exp (-x * x));

	return (x);
}
