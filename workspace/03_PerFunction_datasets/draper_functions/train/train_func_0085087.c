HMAC_CTX_copy(HMAC_CTX *dctx, HMAC_CTX *sctx)
	{
	if (!EVP_MD_CTX_copy(&dctx->i_ctx, &sctx->i_ctx))
		goto err;
	if (!EVP_MD_CTX_copy(&dctx->o_ctx, &sctx->o_ctx))
		goto err;
	if (!EVP_MD_CTX_copy(&dctx->md_ctx, &sctx->md_ctx))
		goto err;
	memcpy(dctx->key, sctx->key, HMAC_MAX_MD_CBLOCK);
	dctx->key_length = sctx->key_length;
	dctx->md = sctx->md;
	return 1;
	err:
	return 0;
	}
