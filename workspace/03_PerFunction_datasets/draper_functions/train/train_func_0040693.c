ZmodF_inverse_butterfly_sqrt2exp(ZmodF_t* a, ZmodF_t* b, ZmodF_t* z,
                                      unsigned long s, unsigned long n)
{
   FLINT_ASSERT(s < 2*n*FLINT_BITS);
   FLINT_ASSERT(*a != *b);
   FLINT_ASSERT(*b != *z);
   FLINT_ASSERT(*a != *z);

   if (s & 1)
   {
      unsigned long limbs, bits;
      ZmodF_decompose_rotation(&limbs, &bits, 2*n*FLINT_BITS - s, n);

      if (n & 1)
         ZmodF_mul_pseudosqrt2_n_odd(*z, *b, 0, n);
      else
         ZmodF_mul_pseudosqrt2_n_even(*z, *b, 0, n);

      if (bits)
         ZmodF_short_div_2exp(*z, *z, bits, n);

      if (limbs == 0)
      {
         ZmodF_add(*b, *a, *z, n);
         ZmodF_sub(*a, *a, *z, n);
      }
      else if (limbs < n)
      {
         ZmodF_div_Bexp_sub(*b, *a, *z, n - limbs, n);
         ZmodF_div_Bexp_add(*a, *a, *z, n - limbs, n);
      }
      else if (limbs == n)
      {
         ZmodF_sub(*b, *a, *z, n);
         ZmodF_add(*a, *a, *z, n);
      }
      else
      {
         ZmodF_div_Bexp_add(*b, *a, *z, 2*n - limbs, n);
         ZmodF_div_Bexp_sub(*a, *a, *z, 2*n - limbs, n);
      }
   }
   else
      ZmodF_inverse_butterfly_2exp(a, b, z, s >> 1, n);
}
