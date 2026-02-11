_nrrdHermite1_d(double x, const double *parm) {
  AIR_UNUSED(parm);
  x = AIR_ABS(x);
  return _TENT(x);
}
