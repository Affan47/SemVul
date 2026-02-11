on20_write_regr( PIA *pi, int cont, int regr, int val )

{	int r;

	r = (regr<<2) + 1 + cont;

	op(1); vl(r);
	op(0); vl(val);
	op(0); vl(val);
}
