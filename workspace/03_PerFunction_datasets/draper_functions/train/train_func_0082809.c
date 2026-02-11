F_mpz_get_ui(const F_mpz_t f)
{
   if (!COEFF_IS_MPZ(*f))
	{
		if (*f < 0L) return -*f;
		else return *f;
	}

	ulong ret = mpz_get_ui(F_mpz_arr + COEFF_TO_OFF(*f));

	return ret;
}
