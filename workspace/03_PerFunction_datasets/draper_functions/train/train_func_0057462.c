hwcrhk_load_pubkey(ENGINE *eng, const char *key_id,
	UI_METHOD *ui_method, void *callback_data)
	{
	EVP_PKEY *res = NULL;

#ifndef OPENSSL_NO_RSA
        res = hwcrhk_load_privkey(eng, key_id,
                ui_method, callback_data);
#endif

	if (res)
		switch(res->type)
			{
#ifndef OPENSSL_NO_RSA
		case EVP_PKEY_RSA:
			{
			RSA *rsa = NULL;

			CRYPTO_w_lock(CRYPTO_LOCK_EVP_PKEY);
			rsa = res->pkey.rsa;
			res->pkey.rsa = RSA_new();
			res->pkey.rsa->n = rsa->n;
			res->pkey.rsa->e = rsa->e;
			rsa->n = NULL;
			rsa->e = NULL;
			CRYPTO_w_unlock(CRYPTO_LOCK_EVP_PKEY);
			RSA_free(rsa);
			}
			break;
#endif
		default:
			HWCRHKerr(HWCRHK_F_HWCRHK_LOAD_PUBKEY,
				HWCRHK_R_CTRL_COMMAND_NOT_IMPLEMENTED);
			goto err;
			}

	return res;
 err:
	if (res)
		EVP_PKEY_free(res);
	return NULL;
	}
