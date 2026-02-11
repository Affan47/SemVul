usr1_deriv(x,partials)
REAL *x;
REAL *partials;
{ REAL denom,cube;
  int i;

  denom = 4+x[0]*x[0]+x[1]*x[1]+x[2]*x[2];
  cube = denom*denom*denom;
  for ( i = 0 ; i < SDIM ; i++ )
     partials[i] = -64/cube*x[i];

  return 16/denom/denom;
}
