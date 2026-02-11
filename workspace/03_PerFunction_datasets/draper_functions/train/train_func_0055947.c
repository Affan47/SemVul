BN_mod_lshift1_quick(BIGNUM *r, const BIGNUM *a, const BIGNUM *m)
	{
	if (!BN_lshift1(r, a)) return 0;
	bn_check_top(r);
	if (BN_cmp(r, m) >= 0)
		return BN_sub(r, r, m);
	return 1;
	}
