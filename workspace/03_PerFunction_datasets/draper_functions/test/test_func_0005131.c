_ZmodF_poly_FFT(ZmodF_t* x, unsigned long depth, unsigned long skip,
                    unsigned long nonzero, unsigned long length,
                    unsigned long twist, unsigned long n,
                    ZmodF_t* scratch)
{
   FLINT_ASSERT((4*n*FLINT_BITS) % (1 << depth) == 0);
   FLINT_ASSERT(skip >= 1);
   FLINT_ASSERT(n >= 1);
   FLINT_ASSERT(nonzero >= 1 && nonzero <= (1 << depth));
   FLINT_ASSERT(length >= 1 && length <= (1 << depth));
   FLINT_ASSERT(depth >= 1);


   if (depth == 1 ||
       ((1 << depth) + 1) * (n+1) <= ZMODFPOLY_FFT_FACTOR_THRESHOLD)
   {
      _ZmodF_poly_FFT_iterative(x, depth, skip, nonzero, length,
                               twist, n, scratch);
   }
   else
   {
      unsigned long rows_depth = depth >> 1;
      unsigned long cols_depth = depth - rows_depth;
      _ZmodF_poly_FFT_factor(x, rows_depth, cols_depth, skip, nonzero, length,
                            twist, n, scratch);
   }
}
