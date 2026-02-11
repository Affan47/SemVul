_c5sept_ANI_Nd(double *f, const double *x, size_t len, const double *parm) {
  double ax, r; unsigned int tmp;
  size_t i;
  AIR_UNUSED(parm);

  for (i=0; i<len; i++) {
    ax = x[i]; ax = AIR_ABS(ax);
    C5SEPT_ANI(r, tmp, ax);
    f[i] = r;
  }
}
