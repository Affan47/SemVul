tenLogSingle_d(double logten[7], const double ten[7]) {
  double eval[3], evec[9];
  unsigned int ii;

  tenEigensolve_d(eval, evec, ten);
  for (ii=0; ii<3; ii++) {
    eval[ii] = log(eval[ii]);
    if (!AIR_EXISTS(eval[ii])) {
      eval[ii] = -FLT_MAX;
    }
  }
  tenMakeSingle_d(logten, ten[0], eval, evec);
}
