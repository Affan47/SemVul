y1f(float x)
{
	float z, s,c,ss,cc,u,v;
	int32_t hx,ix;

	GET_FLOAT_WORD(hx,x);
        ix = 0x7fffffff&hx;

	if(ix>=0x7f800000) return  one/(x+x*x);
        if(ix==0) return -one/zero;
        if(hx<0) return zero/zero;
        if(ix >= 0x40000000) {
                s = sinf(x);
                c = cosf(x);
                ss = -s-c;
                cc = s-c;
                if(ix<0x7f000000) {
                    z = cosf(x+x);
                    if ((s*c)>zero) cc = z/ss;
                    else            ss = z/cc;
                }


                if(ix>0x48000000) z = (invsqrtpi*ss)/sqrtf(x);
                else {
                    u = ponef(x); v = qonef(x);
                    z = invsqrtpi*(u*ss+v*cc)/sqrtf(x);
                }
                return z;
        }
        if(ix<=0x24800000) {
            return(-tpi/x);
        }
        z = x*x;
        u = U0[0]+z*(U0[1]+z*(U0[2]+z*(U0[3]+z*U0[4])));
        v = one+z*(V0[0]+z*(V0[1]+z*(V0[2]+z*(V0[3]+z*V0[4]))));
        return(x*(u/v) + tpi*(j1f(x)*logf(x)-one/x));
}
