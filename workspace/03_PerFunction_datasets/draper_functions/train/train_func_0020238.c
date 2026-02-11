ec_GF2m_simple_cmp(const EC_GROUP *group, const EC_POINT *a, const EC_POINT *b, BN_CTX *ctx)
	{
	BIGNUM *aX, *aY, *bX, *bY;
	BN_CTX *new_ctx = NULL;
	int ret = -1;

	if (EC_POINT_is_at_infinity(group, a))
		{
		return EC_POINT_is_at_infinity(group, b) ? 0 : 1;
		}

	if (EC_POINT_is_at_infinity(group, b))
		return 1;

	if (a->Z_is_one && b->Z_is_one)
		{
		return ((BN_cmp(&a->X, &b->X) == 0) && BN_cmp(&a->Y, &b->Y) == 0) ? 0 : 1;
		}

	if (ctx == NULL)
		{
		ctx = new_ctx = BN_CTX_new();
		if (ctx == NULL)
			return -1;
		}

	BN_CTX_start(ctx);
	aX = BN_CTX_get(ctx);
	aY = BN_CTX_get(ctx);
	bX = BN_CTX_get(ctx);
	bY = BN_CTX_get(ctx);
	if (bY == NULL) goto err;

	if (!EC_POINT_get_affine_coordinates_GF2m(group, a, aX, aY, ctx)) goto err;
	if (!EC_POINT_get_affine_coordinates_GF2m(group, b, bX, bY, ctx)) goto err;
	ret = ((BN_cmp(aX, bX) == 0) && BN_cmp(aY, bY) == 0) ? 0 : 1;

  err:
	if (ctx) BN_CTX_end(ctx);
	if (new_ctx) BN_CTX_free(new_ctx);
	return ret;
	}
