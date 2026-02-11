hartley_hc2r(INT n, const R *x, INT xs, E *o, R *pr)
{
     INT i;
     E sr;

     o[0] = sr = x[0]; o += 1;
     for (i = 1; i + i < n; ++i) {
	  sr += (o[0] = x[i * xs] + x[i * xs]);
	  o[1] = x[(n - i) * xs] + x[(n - i) * xs];
	  o += 2;
     }
     *pr = sr;
}
