_ZmodF_mul_best_fft_depth(unsigned long n, int squaring)
{
   unsigned long* table = squaring ? ZmodF_sqr_fft_table : ZmodF_mul_fft_table;

   unsigned long i;
   for (i = 0; table[i]; i++)
      if (n < table[i])
         return i + 3;


   unsigned long depth = i + 3 +
                 (unsigned long) floor(log(1.0 * n / table[i-1]) / log(4.0));


   while ((n*FLINT_BITS) & ((1 << depth) - 1))
      depth--;

   return depth;
}
