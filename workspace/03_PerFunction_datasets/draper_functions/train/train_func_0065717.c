_nrrdTent1_f(float x, const double *parm) {
  float S;

  S = AIR_CAST(float, parm[0]);
  x = AIR_ABS(x)/S;
  return S ? _TENT(x)/S : x == 0;
}
