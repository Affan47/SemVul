TS_RESP_verify_signature(PKCS7 *token, STACK_OF(X509) *certs,
			     X509_STORE *store, X509 **signer_out)
	{
	STACK_OF(PKCS7_SIGNER_INFO) *sinfos = NULL;
	PKCS7_SIGNER_INFO *si;
	STACK_OF(X509) *signers = NULL;
	X509	*signer;
	STACK_OF(X509) *chain = NULL;
	char	buf[4096];
	int	i, j = 0, ret = 0;
	BIO	*p7bio = NULL;


	if (!token)
		{
		TSerr(TS_F_TS_RESP_VERIFY_SIGNATURE, TS_R_INVALID_NULL_POINTER);
		goto err;
		}


	if(!PKCS7_type_is_signed(token))
		{
		TSerr(TS_F_TS_RESP_VERIFY_SIGNATURE, TS_R_WRONG_CONTENT_TYPE);
		goto err;
		}


	sinfos = PKCS7_get_signer_info(token);
	if (!sinfos || sk_PKCS7_SIGNER_INFO_num(sinfos) != 1)
		{
		TSerr(TS_F_TS_RESP_VERIFY_SIGNATURE,
		      TS_R_THERE_MUST_BE_ONE_SIGNER);
		goto err;
		}
	si = sk_PKCS7_SIGNER_INFO_value(sinfos, 0);


	if (PKCS7_get_detached(token))
		{
		TSerr(TS_F_TS_RESP_VERIFY_SIGNATURE, TS_R_NO_CONTENT);
		goto err;
		}


	signers = PKCS7_get0_signers(token, certs, 0);
	if (!signers || sk_X509_num(signers) != 1) goto err;
	signer = sk_X509_value(signers, 0);


	if (!TS_verify_cert(store, certs, signer, &chain)) goto err;


	if (!TS_check_signing_certs(si, chain)) goto err;


	p7bio = PKCS7_dataInit(token, NULL);


	while ((i = BIO_read(p7bio,buf,sizeof(buf))) > 0);


	j = PKCS7_signatureVerify(p7bio, token, si, signer);
	if (j <= 0)
		{
		TSerr(TS_F_TS_RESP_VERIFY_SIGNATURE, TS_R_SIGNATURE_FAILURE);
		goto err;
		}


	if (signer_out)
		{
		*signer_out = signer;
		CRYPTO_add(&signer->references, 1, CRYPTO_LOCK_X509);
		}

	ret = 1;

 err:
	BIO_free_all(p7bio);
	sk_X509_pop_free(chain, X509_free);
	sk_X509_free(signers);

	return ret;
	}
