_ZmodF_poly_FFT_factor(
            ZmodF_t* x, unsigned long rows_depth, unsigned long cols_depth,
            unsigned long skip, unsigned long nonzero, unsigned long length,
            unsigned long twist, unsigned long n, ZmodF_t* scratch)
{
   FLINT_ASSERT(skip >= 1);
   FLINT_ASSERT(n >= 1);
   FLINT_ASSERT(rows_depth >= 1);
   FLINT_ASSERT(cols_depth >= 1);

   unsigned long depth = rows_depth + cols_depth;
   FLINT_ASSERT((4*n*FLINT_BITS) % (1 << depth) == 0);
   FLINT_ASSERT(nonzero >= 1 && nonzero <= (1 << depth));
   FLINT_ASSERT(length >= 1 && length <= (1 << depth));


   unsigned long root = (4*n*FLINT_BITS) >> depth;
   FLINT_ASSERT(twist < root);

   unsigned long rows = 1UL << rows_depth;
   unsigned long cols = 1UL << cols_depth;

   unsigned long length_rows = length >> cols_depth;
   unsigned long length_cols = length & (cols-1);
   unsigned long length_whole_rows = length_cols ?
                                     (length_rows + 1) : length_rows;
   unsigned long nonzero_rows = nonzero >> cols_depth;
   unsigned long nonzero_cols = nonzero & (cols-1);

   unsigned long i, j;
   ZmodF_t* y;


   for (i = 0, y = x, j = twist; i < nonzero_cols; i++, y += skip, j += root)
      _ZmodF_poly_FFT(y, rows_depth, skip << cols_depth, nonzero_rows + 1,
                     length_whole_rows, j, n, scratch);

   if (nonzero_rows)
   {
      for (; i < cols; i++, y += skip, j += root)
         _ZmodF_poly_FFT(y, rows_depth, skip << cols_depth, nonzero_rows,
                        length_whole_rows, j, n, scratch);
      nonzero_cols = cols;
   }


   for (i = 0, y = x; i < length_rows; i++, y += (skip << cols_depth))
      _ZmodF_poly_FFT(y, cols_depth, skip, nonzero_cols, cols,
                     twist << rows_depth, n, scratch);

   if (length_cols)

      _ZmodF_poly_FFT(y, cols_depth, skip, nonzero_cols, length_cols,
                     twist << rows_depth, n, scratch);
}
