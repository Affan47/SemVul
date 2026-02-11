pkey_rsa_keygen(EVP_PKEY_CTX *ctx, EVP_PKEY *pkey)
	{
	RSA *rsa = NULL;
	RSA_PKEY_CTX *rctx = ctx->data;
	BN_GENCB *pcb, cb;
	int ret;
	if (!rctx->pub_exp)
		{
		rctx->pub_exp = BN_new();
		if (!rctx->pub_exp || !BN_set_word(rctx->pub_exp, RSA_F4))
			return 0;
		}
	rsa = RSA_new();
	if (!rsa)
		return 0;
	if (ctx->pkey_gencb)
		{
		pcb = &cb;
		evp_pkey_set_cb_translate(pcb, ctx);
		}
	else
		pcb = NULL;
	ret = RSA_generate_key_ex(rsa, rctx->nbits, rctx->pub_exp, pcb);
	if (ret > 0)
		EVP_PKEY_assign_RSA(pkey, rsa);
	else
		RSA_free(rsa);
	return ret;
	}
