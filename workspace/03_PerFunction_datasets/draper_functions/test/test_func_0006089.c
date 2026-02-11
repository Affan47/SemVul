s48_integer_or_floanum_mul(long x_1012X, long y_1013X)
{
  long Kdouble_1019X;
  char * addr_1018X;
  double y_1017X;
  long value_1016X;
  double x_1015X;
  long value_1014X;
 {  if ((3 == (3 & x_1012X))) {
    if ((18 == (31 & ((((*((long *) ((((char *) (-3 + x_1012X))) + -8))))>>2))))) {
      Stemp0S = x_1012X;
      Stemp1S = y_1013X;s48_make_availableAgc(16);
      value_1014X = Stemp0S;
      Stemp0S = 1;
      x_1015X = *((double *) (((char *) (-3 + value_1014X))));
      value_1016X = Stemp1S;
      Stemp1S = 1;
      y_1017X = *((double *) (((char *) (-3 + value_1016X))));
      addr_1018X = s48_allocate_small(16);
      *((long *) addr_1018X) = (long) (2122);
      Kdouble_1019X = 3 + (((long) (addr_1018X + 8)));
      *((double *) (((char *) (-3 + Kdouble_1019X)))) = (double) ((x_1015X * y_1017X));
      return Kdouble_1019X;}
    else {
      return integer_multiply(x_1012X, y_1013X);}}
  else {
    return integer_multiply(x_1012X, y_1013X);}}
}
