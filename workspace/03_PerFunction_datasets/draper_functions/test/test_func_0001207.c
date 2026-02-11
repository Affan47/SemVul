F_mpz_get_d_2exp(long * exp, const F_mpz_t f)
{
   F_mpz d = *f;

	if (!COEFF_IS_MPZ(d))
   {
      if (d == 0L)
      {
         (*exp) = 0L;
         return 0.0;
      }
      ulong d_abs = FLINT_ABS(d);
      (*exp) = FLINT_BIT_COUNT(d_abs);
      if (d < 0L) return __gmpn_get_d(&d_abs, 1L, -1L, -*exp);
      else return __gmpn_get_d(&d, 1L, 1L, -*exp);
   } else
	{

		double ret = mpz_get_d_2exp(exp, F_mpz_arr + COEFF_TO_OFF(d));

		return ret;
	}
}
