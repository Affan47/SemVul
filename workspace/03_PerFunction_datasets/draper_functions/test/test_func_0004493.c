pkey_dsa_paramgen(EVP_PKEY_CTX *ctx, EVP_PKEY *pkey)
	{
	DSA *dsa = NULL;
	DSA_PKEY_CTX *dctx = ctx->data;
	BN_GENCB *pcb, cb;
	int ret;
	if (ctx->pkey_gencb)
		{
		pcb = &cb;
		evp_pkey_set_cb_translate(pcb, ctx);
		}
	else
		pcb = NULL;
	dsa = DSA_new();
	if (!dsa)
		return 0;
	ret = dsa_builtin_paramgen(dsa, dctx->nbits, dctx->qbits, dctx->pmd,
	                           NULL, 0, NULL, NULL, NULL, pcb);
	if (ret)
		EVP_PKEY_assign_DSA(pkey, dsa);
	else
		DSA_free(dsa);
	return ret;
	}
