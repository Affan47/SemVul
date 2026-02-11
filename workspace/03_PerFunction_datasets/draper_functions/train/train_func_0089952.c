sparse_hessian_times_B_kronecker_C(mwIndex *isparseA, mwIndex *jsparseA, double *vsparseA,
                                   double *B, double *C, double *D,
                                   mwSize mA, mwSize nA, mwSize mB, mwSize nB, mwSize mC, mwSize nC, int number_of_threads)
{


#if USE_OMP
# pragma omp parallel for num_threads(number_of_threads)
#endif
  for (mwIndex jj = 0; jj < nB*nC; jj++)
    {

#if DEBUG_OMP
      mexPrintf("%d thread number is %d (%d).\n", jj, omp_get_thread_num(), omp_get_num_threads());
#endif
      mwIndex jB = jj/nC;
      mwIndex jC = jj%nC;
      mwIndex k1 = 0;
      mwIndex k2 = 0;
      mwIndex iv = 0;
      int nz_in_column_ii_of_A = 0;


      for (mwIndex ii = 0; ii < nA; ii++)
        {
          k1 = jsparseA[ii];
          k2 = jsparseA[ii+1];
          if (k1 < k2)
            {
              ++nz_in_column_ii_of_A;
              mwIndex iC = (ii%mB);
              mwIndex iB = (ii/mB);
              double cb = C[jC*mC+iC]*B[jB*mB+iB];


              for (mwIndex k = k1; k < k2; k++)
                {
                  mwIndex kk = isparseA[k];
                  D[jj*mA+kk] = D[jj*mA+kk] + cb*vsparseA[iv];
                  iv++;
                }
            }
        }
    }
}
