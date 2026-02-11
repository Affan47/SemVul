modin(Integer& res, const Integer& n)
	{
		if (isZero(res)) return res;

		mpz_mod( (mpz_ptr)&res.gmp_rep, (mpz_ptr)&res.gmp_rep, (mpz_srcptr)&n.gmp_rep );
		return res;
	}
