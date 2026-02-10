poly_basis_fn(ssize_t n, double x, double y)
{

  switch(n) {
    case  0:  return( 1.0 );
    case  1:  return(  x  );
    case  2:  return(  y  );
    case  3:  return( x*y );
    case  4:  return( x*x );
    case  5:  return( y*y );
    case  6:  return( x*x*x );
    case  7:  return( x*x*y );
    case  8:  return( x*y*y );
    case  9:  return( y*y*y );
    case 10:  return( x*x*x*x );
    case 11:  return( x*x*x*y );
    case 12:  return( x*x*y*y );
    case 13:  return( x*y*y*y );
    case 14:  return( y*y*y*y );
    case 15:  return( x*x*x*x*x );
    case 16:  return( x*x*x*x*y );
    case 17:  return( x*x*x*y*y );
    case 18:  return( x*x*y*y*y );
    case 19:  return( x*y*y*y*y );
    case 20:  return( y*y*y*y*y );
  }
  return( 0 );
}
