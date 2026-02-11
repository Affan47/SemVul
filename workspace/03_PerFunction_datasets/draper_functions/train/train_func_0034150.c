torus_wrap(x,y,wrap)
REAL *x;
REAL *y;
WRAPTYPE wrap;
{
  int i,j;
  int wrapnum;

  if ( x != y )
     for ( i = 0 ; i < SDIM ; i++ ) y[i] = x[i];
  for ( i = 0 ; wrap != 0 ; i++, wrap >>= TWRAPBITS )
  { wrapnum =  WRAPNUM(wrap & WRAPMASK);
    if ( wrapnum )
       for ( j = 0 ; j < SDIM ; j++ )
          y[j] += wrapnum*web.torus_period[i][j];
  }
}
