_nrrdBCN_f(float *f, const float *x, size_t len, const double *parm) {
  float S, t, B, C;
  size_t i;

  S = AIR_CAST(float, parm[0]);
  B = AIR_CAST(float, parm[1]);
  C = AIR_CAST(float, parm[2]);
  for (i=0; i<len; i++) {
    t = x[i];
    t = AIR_ABS(t)/S;
    f[i] = _BCCUBIC(t, B, C)/S;
  }
}
