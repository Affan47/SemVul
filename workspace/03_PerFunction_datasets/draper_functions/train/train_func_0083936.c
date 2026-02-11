__scalblnl (long double x, long int n)
{
	int32_t k,es,hx,lx;
	GET_LDOUBLE_WORDS(es,hx,lx,x);
	k = es&0x7fff;
	if (__builtin_expect(k==0, 0)) {
	    if ((lx|(hx&0x7fffffff))==0) return x;
	    x *= two63;
	    GET_LDOUBLE_EXP(es,x);
	    k = (hx&0x7fff) - 63;
	    }
	if (__builtin_expect(k==0x7fff, 0)) return x+x;
	if (__builtin_expect(n< -50000, 0))
	  return tiny*__copysignl(tiny,x);
	if (__builtin_expect(n> 50000 || k+n > 0x7ffe, 0))
	  return huge*__copysignl(huge,x);


	k = k+n;
	if (__builtin_expect(k > 0, 1))
	    {SET_LDOUBLE_EXP(x,(es&0x8000)|k); return x;}
	if (k <= -63)
	    return tiny*__copysignl(tiny,x);
	k += 63;
	SET_LDOUBLE_EXP(x,(es&0x8000)|k);
	return x*twom63;
}
