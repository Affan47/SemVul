ec_GFp_simple_group_check_discriminant(const EC_GROUP *group, BN_CTX *ctx)
	{
	int ret = 0;
	BIGNUM *a,*b,*order,*tmp_1,*tmp_2;
	const BIGNUM *p = &group->field;
	BN_CTX *new_ctx = NULL;

	if (ctx == NULL)
		{
		ctx = new_ctx = BN_CTX_new();
		if (ctx == NULL)
			{
			ECerr(EC_F_EC_GFP_SIMPLE_GROUP_CHECK_DISCRIMINANT, ERR_R_MALLOC_FAILURE);
			goto err;
			}
		}
	BN_CTX_start(ctx);
	a = BN_CTX_get(ctx);
	b = BN_CTX_get(ctx);
	tmp_1 = BN_CTX_get(ctx);
	tmp_2 = BN_CTX_get(ctx);
	order = BN_CTX_get(ctx);
	if (order == NULL) goto err;

	if (group->meth->field_decode)
		{
		if (!group->meth->field_decode(group, a, &group->a, ctx)) goto err;
		if (!group->meth->field_decode(group, b, &group->b, ctx)) goto err;
		}
	else
		{
		if (!BN_copy(a, &group->a)) goto err;
		if (!BN_copy(b, &group->b)) goto err;
		}


	if (BN_is_zero(a))
		{
		if (BN_is_zero(b)) goto err;
		}
	else if (!BN_is_zero(b))
		{
		if (!BN_mod_sqr(tmp_1, a, p, ctx)) goto err;
		if (!BN_mod_mul(tmp_2, tmp_1, a, p, ctx)) goto err;
		if (!BN_lshift(tmp_1, tmp_2, 2)) goto err;


		if (!BN_mod_sqr(tmp_2, b, p, ctx)) goto err;
		if (!BN_mul_word(tmp_2, 27)) goto err;


		if (!BN_mod_add(a, tmp_1, tmp_2, p, ctx)) goto err;
		if (BN_is_zero(a)) goto err;
		}
	ret = 1;

err:
	if (ctx != NULL)
		BN_CTX_end(ctx);
	if (new_ctx != NULL)
		BN_CTX_free(new_ctx);
	return ret;
	}
