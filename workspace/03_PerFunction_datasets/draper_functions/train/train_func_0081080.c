ec_GFp_nist_field_mul(const EC_GROUP *group, BIGNUM *r, const BIGNUM *a,
	const BIGNUM *b, BN_CTX *ctx)
	{
	int	ret=0;
	BN_CTX	*ctx_new=NULL;

	if (!group || !r || !a || !b)
		{
		ECerr(EC_F_EC_GFP_NIST_FIELD_MUL, ERR_R_PASSED_NULL_PARAMETER);
		goto err;
		}
	if (!ctx)
		if ((ctx_new = ctx = BN_CTX_new()) == NULL) goto err;

	if (!BN_mul(r, a, b, ctx)) goto err;
	if (!group->field_mod_func(r, r, &group->field, ctx))
		goto err;

	ret=1;
err:
	if (ctx_new)
		BN_CTX_free(ctx_new);
	return ret;
	}
