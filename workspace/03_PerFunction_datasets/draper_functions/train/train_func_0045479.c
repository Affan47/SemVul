central_wrap(x,y,wrap)
 REAL *x;
 REAL *y;
 WRAPTYPE wrap;
 { int n;
   for ( n = 0 ; n < SDIM ; n++ ) y[n] = wrap ? -x[n] : x[n];
 }
