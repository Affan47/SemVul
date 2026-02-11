_nrrd_TMF_d2_c1_4ef_1_d(double x, const double *parm) {
  int i;


  x += 4;
  i = (int)((x<0) ? x-1 : x);
  x -= i;
  return TMF_d2_c1_4ef(parm[0], i, x);
}
