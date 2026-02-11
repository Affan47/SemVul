doubletoIEEE754_64(double d) {
	ORD32 sn = 0, ep = 0;
	ORD64 ma, id;


	if (d < 0.0) {
		sn = 1;
		d = -d;
	}
	if (d != 0.0) {
		int ee;
		ee = (int)floor(log(d)/log(2.0));
		if (ee < -1022)
			ee = -1022;
		d *= pow(0.5, (double)(ee - 52));
		ee += 1023;
		if (ee < 1)
			ee = 0;
		else if (ee > 2046) {
			ee = 2047;
			d = 0.0;
		}
		ep = ee;
	} else {
		ep = 0;
	}
	ma = ((ORD64)d) & (((ORD64)1 << 52)-1);
	id = ((ORD64)sn << 63) | ((ORD64)ep << 52) | ma;

	return id;
}
