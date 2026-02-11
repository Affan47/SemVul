ATL_sreftrsvUNU
(
   const int                  N,
   const float                * A,
   const int                  LDA,
   float                      * X,
   const int                  INCX
)
{


   register float             t0;
   int                        i, iaij, ix, j, jaj, jx;


   for( j = N-1,     jaj  = (N-1)*LDA, jx  = (N-1)*INCX;
        j >= 0; j--, jaj -= LDA,       jx -= INCX )
   {
      t0 = X[jx];
      for( i = 0, iaij = jaj, ix = 0; i < j; i++, iaij += 1, ix += INCX )
      { X[ix] -= t0 * A[iaij]; }
   }


}
