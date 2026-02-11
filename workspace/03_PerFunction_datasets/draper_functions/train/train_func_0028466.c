mympz_is_prime (mpz_srcptr n, int miller_rabin_reps)
{
	int ret;
	static mpz_t test;
	static gboolean inited_test = FALSE;
	int sgn;

	sgn = mpz_sgn (n);
	if (sgn == 0)
		return 0;
	else if (sgn < 0) {
		mpz_t nn;
		mpz_init (nn);
		mpz_neg (nn, n);
		ret = mympz_is_prime (nn, miller_rabin_reps);
		mpz_clear (nn);
		return ret;
	}

	if (miller_rabin_reps < 0)
		miller_rabin_reps = mympz_is_prime_miller_rabin_reps;


	ret = mpz_probab_prime_p (n, 1);

	if (ret == 2)
		return 1;
	else if (ret == 0)
		return 0;

	if ( ! mympz_strong_pseudoprime_test_2_3_5_7 (n))
		return 0;

	if G_UNLIKELY ( ! inited_test) {

		mpz_init_set_ui (test, 10);
		mpz_pow_ui (test, test, 9);
		mpz_mul_ui (test, test, 25);

		inited_test = TRUE;
	}


	if (mpz_cmp (n, test) <= 0)
		return 1;

	if (gel_evalnode_hook != NULL)
		(*gel_evalnode_hook)();
	if G_UNLIKELY (gel_interrupted)
		return 0;

	return mpz_millerrabin (n, miller_rabin_reps-1);
}
