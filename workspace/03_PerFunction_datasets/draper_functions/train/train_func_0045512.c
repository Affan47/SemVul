__frexpl(long double x, int *eptr)
{
	u_int32_t se, hx, ix, lx;
	GET_LDOUBLE_WORDS(se,hx,lx,x);
	ix = 0x7fff&se;
	*eptr = 0;
	if(ix==0x7fff||((ix|hx|lx)==0)) return x;
	if (ix==0x0000) {
	    x *= two65;
	    GET_LDOUBLE_EXP(se,x);
	    ix = se&0x7fff;
	    *eptr = -65;
	}
	*eptr += ix-16382;
	se = (se & 0x8000) | 0x3ffe;
	SET_LDOUBLE_EXP(x,se);
	return x;
}
