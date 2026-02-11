_nrrdDiscGaussianInt(const double *parm) {
  double sum, cut;
  int ii, supp;

  _DGABSCUT(cut, parm[0], parm[1]);
  supp = AIR_CAST(int, cut);
  sum = 0.0;
  for (ii=-supp; ii<=supp; ii++) {
    sum += _nrrdDiscGaussian1_d(ii, parm);
  }
  return sum;
}
