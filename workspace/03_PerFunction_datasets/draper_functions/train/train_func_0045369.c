F_mpz_set(F_mpz_t f, const F_mpz_t g)
{
	if (f == g) return;

	if (!COEFF_IS_MPZ(*g))
	{

		_F_mpz_demote(f);

		*f = *g;
	} else
	{

		__mpz_struct * mpz_ptr = _F_mpz_promote(f);
		mpz_set(mpz_ptr, F_mpz_arr + COEFF_TO_OFF(*g));

	}
}
