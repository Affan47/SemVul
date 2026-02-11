compare_matrices(char mat_name,
                 const real *computed, const long double *ref, int sz,
                 ergo_real eps)
{
  bool failed = false;

  for(int row=0; row<sz; row++) {
    for(int col=0; col<sz; col++) {
      ergo_real theDiff = computed[row + col*sz]- ref[row+col*sz];
      bool ok1 = false;
      if(theDiff > -std::numeric_limits<ergo_real>::max())
        ok1 = true;
      bool ok2 = false;
      if(theDiff < std::numeric_limits<ergo_real>::max())
        ok2 = true;
      if( ! (ok1 && ok2) ) {
        printf("Error! nan/inf found in compare_matrices().\n");
        failed = true;
      }
      if (std::fabs(theDiff)>eps) {
        printf("%c (%d,%d): ref: %28.25Lf got: %28.25Lf diff: %12g eps: %g\n",
               mat_name, row, col,
               (long double)ref[row + col*sz],
               (long double)computed[row + col*sz],
               (double)(computed[row + col*sz]- ref[row+col*sz]),
               (double)eps);
        failed = true;
      }
    }
  }
  return failed;
}
