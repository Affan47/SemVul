_nrrdCDN_f(float *f, const float *x, size_t len, const double *parm) {
  float t, S;
  size_t i;

  S = AIR_CAST(float, parm[0]);
  for (i=0; i<len; i++) {
    t = x[i]/S;
    f[i] = AIR_CAST(float, _CENDIF(t)/(S*S));
  }
}
