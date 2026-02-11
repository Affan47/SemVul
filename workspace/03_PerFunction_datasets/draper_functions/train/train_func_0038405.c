tanl(long double x)
{
	union IEEEl2bits z;
	int e0, s;
	long double y[2];
	long double hi, lo;

	z.e = x;
	s = z.bits.sign;
	z.bits.sign = 0;


	if (z.bits.exp == 0)
		return (x);


	if (z.bits.exp == 32767)
		return ((x - x) / (x - x));


	if (z.e < M_PI_4) {
		hi = __kernel_tanl(z.e, 0, 0);
		return (s ? -hi : hi);
	}

	e0 = __ieee754_rem_pio2l(x, y);
	hi = y[0];
	lo = y[1];

	switch (e0 & 3) {
	case 0:
	case 2:
	    hi = __kernel_tanl(hi, lo, 0);
	    break;
	case 1:
	case 3:
	    hi = __kernel_tanl(hi, lo, 1);
	    break;
	}

	return (hi);
}
