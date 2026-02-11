F_mpz_get_si(const F_mpz_t f)
{
   if (!COEFF_IS_MPZ(*f)) return *f;

	long ret = mpz_get_si(F_mpz_arr + COEFF_TO_OFF(*f));

	return ret;
}
