compare_matrices(const std::vector<ergo_real> & A,
			   const std::vector<ergo_real> & B,
			   int n) {
  ergo_real maxabsdiff = 0;
  for(int i = 0; i < n*n; i++) {
    ergo_real absdiff = fabs(A[i] - B[i]);
    if(absdiff > maxabsdiff)
      maxabsdiff = absdiff;
  }
  return maxabsdiff;
}
