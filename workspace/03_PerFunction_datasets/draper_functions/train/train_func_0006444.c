casin(double complex z)
{
	double complex w;
	static double complex ca, ct, zz, z2;
	double x, y;

	x = creal (z);
	y = cimag (z);

	if (y == 0.0) {
		if (fabs(x) > 1.0) {
			w = M_PI_2 + 0.0 * I;

		}
		else {
			w = asin (x) + 0.0 * I;
		}
		return (w);
	}


	ca = x + y * I;
	ct = ca * I;


	zz = (x - y) * (x + y) + (2.0 * x * y) * I;

	zz = 1.0 - creal(zz) - cimag(zz) * I;
	z2 = csqrt (zz);

	zz = ct + z2;
	zz = clog (zz);

	w = zz * (-1.0 * I);
	return (w);
}
