__ieee754_yn(int n, double x)
#else
	double __ieee754_yn(n,x)
	int n; double x;
#endif
{
	int i,hx,ix,lx;
	int sign;
	double a, b, temp;

        EXTRACT_WORDS(hx, lx, x);
	ix = 0x7fffffff&hx;

	if((ix|((unsigned)(lx|-lx))>>31)>0x7ff00000) return x+x;
	if((ix|lx)==0) return -one/zero;
	if(hx<0) return zero/zero;
	sign = 1;
	if(n<0){
		n = -n;
		sign = 1 - ((n&1)<<1);
	}
	if(n==0) return(__ieee754_y0(x));
	if(n==1) return(sign*__ieee754_y1(x));
	if(ix==0x7ff00000) return zero;
	if(ix>=0x52D00000) {


		switch(n&3) {
		    case 0: temp =  sin(x)-cos(x); break;
		    case 1: temp = -sin(x)-cos(x); break;
		    case 2: temp = -sin(x)+cos(x); break;
		    case 3: temp =  sin(x)+cos(x); break;
		}
		b = invsqrtpi*temp/sqrt(x);
	} else {
	    a = __ieee754_y0(x);
	    b = __ieee754_y1(x);

            int hb;
            GET_HIGH_WORD(hb, b);
	    for(i=1;i<n&&(hb != 0xfff00000);i++){
		temp = b;
		b = ((double)(i+i)/x)*b - a;
                GET_HIGH_WORD(hb, b);
		a = temp;
	    }
	}
	if(sign>0) return b; else return -b;
}
