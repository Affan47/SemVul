zn_mod_pow (ulong x, long k, const zn_mod_t mod)
{
   ZNP_ASSERT (k >= 0);


   ulong prod = 1;
   ulong x_pow = x;
   for (; k; k >>= 1)
   {
      if (k & 1)
         prod = zn_mod_mul (prod, x_pow, mod);
      x_pow = zn_mod_mul (x_pow, x_pow, mod);
   }
   return prod;
}
