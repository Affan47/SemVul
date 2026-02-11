cexpf(float complex z)
{
	float x, y, exp_x;
	u_int32_t hx, hy;

	x = crealf(z);
	y = cimagf(z);

	GET_FLOAT_WORD(hy, y);
	hy &= 0x7fffffff;


	if (hy == 0)
		return (cpackf(expf(x), y));
	GET_FLOAT_WORD(hx, x);

	if ((hx & 0x7fffffff) == 0)
		return (cpackf(cosf(y), sinf(y)));

	if (hy >= 0x7f800000) {
		if ((hx & 0x7fffffff) != 0x7f800000) {

			return (cpackf(y - y, y - y));
		} else if (hx & 0x80000000) {

			return (cpackf(0.0, 0.0));
		} else {

			return (cpackf(x, y - y));
		}
	}

	if (hx >= exp_ovfl && hx <= cexp_ovfl) {


		return (__ldexp_cexpf(z, 0));
	} else {


		exp_x = expf(x);
		return (cpackf(exp_x * cosf(y), exp_x * sinf(y)));
	}
}
