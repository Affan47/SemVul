ATL_cgpKBmm(const int M, const int N, const int K, const float alpha, const float *A, const int lda, const float *B, const int ldb, const float beta, float *C, const int ldc)
{
   static MMfunc mmfunc[  1] = {
                         ATL_cJIK0x0x56TN56x56x0_a1_bX,
                        };
   MMfunc mm;

   if (K <= 55)
   {
      ATL_cJIK0x0x0TN0x0x0_a1_bX(M, N, K, alpha, A, lda, B, ldb, -beta, C, ldc);
      ATL_cJIK0x0x0TN0x0x0_a1_bX(M, N, K, alpha, A, lda, B+N*ldb, ldb, beta, C+1, ldc);
      ATL_cJIK0x0x0TN0x0x0_a1_bX(M, N, K, alpha, A+M*lda, lda, B+N*ldb, ldb, -1.0, C, ldc);
      ATL_cJIK0x0x0TN0x0x0_a1_bX(M, N, K, alpha, A+M*lda, lda, B, ldb, 1.0, C+1, ldc);
   }
   else
   {
      mm = mmfunc[K-56];
      mm(M, N, K, alpha, A, lda, B, ldb, -beta, C, ldc);
      mm(M, N, K, alpha, A, lda, B+N*ldb, ldb, beta, C+1, ldc);
      mm(M, N, K, alpha, A+M*lda, lda, B+N*ldb, ldb, -1.0, C, ldc);
      mm(M, N, K, alpha, A+M*lda, lda, B, ldb, 1.0, C+1, ldc);
   }
}
