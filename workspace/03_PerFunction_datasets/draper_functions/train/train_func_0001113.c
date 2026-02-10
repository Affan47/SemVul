svdLAS2A(SMat A, long dimensions) {
  double end[2] = {-1.0e-30, 1.0e-30};
  double kappa = 1e-6;
  if (!A) {
    svd_error("svdLAS2A called with NULL array\n");
    return NULL;
  }
  return svdLAS2(A, dimensions, 0, end, kappa);
}
