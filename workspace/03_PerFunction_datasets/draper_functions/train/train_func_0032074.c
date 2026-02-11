cipher_chaos_getbyte(double *x, int y) {
	static int i=0;

	NORM(*x);
	FIX(*x);
	BEST(*x,y);
	*x=(double) (R(*x)*(1-*x));
	i++;
SPOTVAR_NUM(y);
	return((unsigned char) y);
}
