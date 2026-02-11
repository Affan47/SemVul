_nrrd_TMF_d0_c0_1ef_1_f(float x, const double *parm) {
  int i;

  AIR_UNUSED(parm);
  x += 1;
  i = (int)((x<0) ? x-1 : x);
  x -= AIR_CAST(float, i);
  return AIR_CAST(float, TMF_d0_c0_1ef(parm[0], i, x));
}
