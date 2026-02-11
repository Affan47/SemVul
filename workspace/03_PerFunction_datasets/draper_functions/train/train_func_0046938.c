__scalblnf (float x, long int n)
{
	int32_t k,ix;
	GET_FLOAT_WORD(ix,x);
	k = (ix&0x7f800000)>>23;
	if (__builtin_expect(k==0, 0)) {
	    if ((ix&0x7fffffff)==0) return x;
	    x *= two25;
	    GET_FLOAT_WORD(ix,x);
	    k = ((ix&0x7f800000)>>23) - 25;
	    }
	if (__builtin_expect(k==0xff, 0)) return x+x;
	if (__builtin_expect(n< -50000, 0))
	  return tiny*copysignf(tiny,x);
	if (__builtin_expect(n> 50000 || k+n > 0xfe, 0))
	  return huge*copysignf(huge,x);


	k = k+n;
	if (__builtin_expect(k > 0, 1))
	    {SET_FLOAT_WORD(x,(ix&0x807fffff)|(k<<23)); return x;}
	if (k <= -25)
	    return tiny*copysignf(tiny,x);
	k += 25;
	SET_FLOAT_WORD(x,(ix&0x807fffff)|(k<<23));
	return x*twom25;
}
