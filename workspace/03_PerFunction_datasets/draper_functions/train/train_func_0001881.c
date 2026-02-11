__kernel_cos(double x, double y)
#else
	double __kernel_cos(x, y)
	double x,y;
#endif
{
	double a,hz,z,r,qx;
	int ix;
        GET_HIGH_WORD(ix, x);
	ix &= 0x7fffffff;
	if(ix<0x3e400000) {
	    if(((int)x)==0) return one;
	}
	z  = x*x;
	r  = z*(C1+z*(C2+z*(C3+z*(C4+z*(C5+z*C6)))));
	if(ix < 0x3FD33333)
	    return one - (0.5*z - (z*r - x*y));
	else {
	    if(ix > 0x3fe90000) {
		qx = 0.28125;
	    } else {
                INSERT_WORDS(qx, ix-0x00200000, 0);
	    }
	    hz = 0.5*z-qx;
	    a  = one-qx;
	    return a - (hz - (z*r-x*y));
	}
}
