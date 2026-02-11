EC_KEY_check_key(const EC_KEY *eckey)
	{
	int	ok   = 0;
	BN_CTX	*ctx = NULL;
	const BIGNUM	*order  = NULL;
	EC_POINT *point = NULL;

	if (!eckey || !eckey->group || !eckey->pub_key)
		{
		ECerr(EC_F_EC_KEY_CHECK_KEY, ERR_R_PASSED_NULL_PARAMETER);
		return 0;
		}

	if (EC_POINT_is_at_infinity(eckey->group, eckey->pub_key))
		{
		ECerr(EC_F_EC_KEY_CHECK_KEY, EC_R_POINT_AT_INFINITY);
		goto err;
		}

	if ((ctx = BN_CTX_new()) == NULL)
		goto err;
	if ((point = EC_POINT_new(eckey->group)) == NULL)
		goto err;


	if (!EC_POINT_is_on_curve(eckey->group, eckey->pub_key, ctx))
		{
		ECerr(EC_F_EC_KEY_CHECK_KEY, EC_R_POINT_IS_NOT_ON_CURVE);
		goto err;
		}

	order = &eckey->group->order;
	if (BN_is_zero(order))
		{
		ECerr(EC_F_EC_KEY_CHECK_KEY, EC_R_INVALID_GROUP_ORDER);
		goto err;
		}
	if (!EC_POINT_mul(eckey->group, point, NULL, eckey->pub_key, order, ctx))
		{
		ECerr(EC_F_EC_KEY_CHECK_KEY, ERR_R_EC_LIB);
		goto err;
		}
	if (!EC_POINT_is_at_infinity(eckey->group, point))
		{
		ECerr(EC_F_EC_KEY_CHECK_KEY, EC_R_WRONG_ORDER);
		goto err;
		}


	if (eckey->priv_key)
		{
		if (BN_cmp(eckey->priv_key, order) >= 0)
			{
			ECerr(EC_F_EC_KEY_CHECK_KEY, EC_R_WRONG_ORDER);
			goto err;
			}
		if (!EC_POINT_mul(eckey->group, point, eckey->priv_key,
			NULL, NULL, ctx))
			{
			ECerr(EC_F_EC_KEY_CHECK_KEY, ERR_R_EC_LIB);
			goto err;
			}
		if (EC_POINT_cmp(eckey->group, point, eckey->pub_key,
			ctx) != 0)
			{
			ECerr(EC_F_EC_KEY_CHECK_KEY, EC_R_INVALID_PRIVATE_KEY);
			goto err;
			}
		}
	ok = 1;
err:
	if (ctx   != NULL)
		BN_CTX_free(ctx);
	if (point != NULL)
		EC_POINT_free(point);
	return(ok);
	}
