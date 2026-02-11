complexSqrt(complex_ z)
{
	complex_ c;
	double x, y, w, r;
	if ((z.r == 0.0) && (z.i == 0.0)) {
		c.i = 0.0;
		c.r = 0.0;
	} else {
		x = fabs(z.r);
		y = fabs(z.i);
		if (x >= y) {
			r = y/x;
			w = sqrt(x)*sqrt(0.5*(1.0+sqrt(1.0+r*r)));
		} else {
			r=x/y;
			w = sqrt(y)*sqrt(0.5*(r+sqrt(1.0+r*r)));
		}
		if (z.r >= 0.0) {
			c.r = w;
			c.i = z.i/(2.0*w);
		} else {
			c.i = (z.i >= 0) ? w : -w;
			c.r = z.i/(2.0*c.i);
		}
	}
	return c;
}
