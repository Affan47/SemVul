__ieee754_asinf(float x)
{
	float t,w,p,q,c,r,s;
	int32_t hx,ix;
	GET_FLOAT_WORD(hx,x);
	ix = hx&0x7fffffff;
	if(ix==0x3f800000) {

	    return x*pio2_hi+x*pio2_lo;
	} else if(ix> 0x3f800000) {
	    return (x-x)/(x-x);
	} else if (ix<0x3f000000) {
	    if(ix<0x32000000) {
		if(huge+x>one) return x;
	    } else {
		t = x*x;
		w = t * (p0 + t * (p1 + t * (p2 + t * (p3 + t * p4))));
		return x+x*w;
	    }
	}

	w = one-fabsf(x);
	t = w*0.5f;
	p = t * (p0 + t * (p1 + t * (p2 + t * (p3 + t * p4))));
	s = __ieee754_sqrtf(t);
	if(ix>=0x3F79999A) {
	    t = pio2_hi-(2.0f*(s+s*p)-pio2_lo);
	} else {
	    int32_t iw;
	    w  = s;
	    GET_FLOAT_WORD(iw,w);
	    SET_FLOAT_WORD(w,iw&0xfffff000);
	    c  = (t-w*w)/(s+w);
	    r  = p;
	    p  = 2.0f*s*r-(pio2_lo-2.0f*c);
	    q  = pio4_hi-2.0f*w;
	    t  = pio4_hi-(p-q);
	}
	if(hx>0) return t; else return -t;
}
