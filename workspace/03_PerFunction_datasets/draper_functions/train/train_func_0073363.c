do_sign_init(BIO *err, EVP_MD_CTX *ctx, EVP_PKEY *pkey,
			const EVP_MD *md, STACK_OF(OPENSSL_STRING) *sigopts)
	{
	EVP_PKEY_CTX *pkctx = NULL;
	int i;
	EVP_MD_CTX_init(ctx);
	if (!EVP_DigestSignInit(ctx, &pkctx, md, NULL, pkey))
		return 0;
	for (i = 0; i < sk_OPENSSL_STRING_num(sigopts); i++)
		{
		char *sigopt = sk_OPENSSL_STRING_value(sigopts, i);
		if (pkey_ctrl_string(pkctx, sigopt) <= 0)
			{
			BIO_printf(err, "parameter error \"%s\"\n", sigopt);
			ERR_print_errors(bio_err);
			return 0;
			}
		}
	return 1;
	}
