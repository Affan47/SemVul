_nrrdZero1_d(double x, const double *parm) {
  double S;

  S = parm[0];
  x = AIR_ABS(x)/S;
  return _ZERO(x)/S;
}
