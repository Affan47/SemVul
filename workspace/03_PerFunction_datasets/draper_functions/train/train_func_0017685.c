_dddc5sept1_f(float x, const double *parm) {
  unsigned int xi;
  int sgn = 1;
  AIR_UNUSED(parm);
  if (x < 0) { x = -x; sgn = -1; }
  xi = AIR_CAST(unsigned int, x);
  x -= AIR_CAST(float, xi);
  return AIR_CAST(float, sgn*_DDDC5SEPT(xi, x));
}
