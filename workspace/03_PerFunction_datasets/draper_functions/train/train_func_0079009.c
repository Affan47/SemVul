_nrrd_TMF_d1_c0_4ef_N_f(float *f, const float *x, size_t len, const double *parm) {
  float t;
  size_t I;
  int i;


  for (I=0; I<len; I++) {
    t = x[I] + 3;
    i = (int)((t<0) ? t-1 : t);
    t -= AIR_CAST(float, i);
    f[I] = AIR_CAST(float, TMF_d1_c0_4ef(parm[0], i, t));
  }
}
