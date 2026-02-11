_nrrd_TMF_d2_c1_4ef_N_d(double *f, const double *x, size_t len, const double *parm) {
  double t;
  size_t I;
  int i;


  for (I=0; I<len; I++) {
    t = x[I] + 4;
    i = (int)((t<0) ? t-1 : t);
    t -= i;
    f[I] = TMF_d2_c1_4ef(parm[0], i, t);
  }
}
