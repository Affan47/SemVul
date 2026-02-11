_nrrd_TMF_d2_c1_3ef_1_f(float x, const double *parm) {
  int i;

  AIR_UNUSED(parm);
  x += 3;
  i = (int)((x<0) ? x-1 : x);
  x -= AIR_CAST(float, i);
  return AIR_CAST(float, TMF_d2_c1_3ef(parm[0], i, x));
}
