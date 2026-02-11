BN_mod_lshift1(BIGNUM *r, const BIGNUM *a, const BIGNUM *m, BN_CTX *ctx)
	{
	if (!BN_lshift1(r, a)) return 0;
	bn_check_top(r);
	return BN_nnmod(r, r, m, ctx);
	}
