sfpow10(reg int n)
#else
static Sfdouble_t sfpow10(n)
reg int n;
#endif
{
    Sfdouble_t dval;

    switch (n) {
    case -3:
	return .001;
    case -2:
	return .01;
    case -1:
	return .1;
    case 0:
	return 1.;
    case 1:
	return 10.;
    case 2:
	return 100.;
    case 3:
	return 1000.;
    }

    if (n < 0) {
	dval = .0001;
	for (n += 4; n < 0; n += 1)
	    dval /= 10.;
    } else {
	dval = 10000.;
	for (n -= 4; n > 0; n -= 1)
	    dval *= 10.;
    }

    return dval;
}
