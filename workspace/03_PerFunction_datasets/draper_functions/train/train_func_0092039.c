BN_mod_mul(BIGNUM *r, const BIGNUM *a, const BIGNUM *b, const BIGNUM *m,
	BN_CTX *ctx)
	{
	BIGNUM *t;
	int ret=0;

	bn_check_top(a);
	bn_check_top(b);
	bn_check_top(m);

	BN_CTX_start(ctx);
	if ((t = BN_CTX_get(ctx)) == NULL) goto err;
	if (a == b)
		{ if (!BN_sqr(t,a,ctx)) goto err; }
	else
		{ if (!BN_mul(t,a,b,ctx)) goto err; }
	if (!BN_nnmod(r,t,m,ctx)) goto err;
	bn_check_top(r);
	ret=1;
err:
	BN_CTX_end(ctx);
	return(ret);
	}
