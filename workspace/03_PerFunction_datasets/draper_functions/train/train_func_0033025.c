PKCS5_pbe2_set_iv(const EVP_CIPHER *cipher, int iter,
				 unsigned char *salt, int saltlen,
				 unsigned char *aiv, int prf_nid)
{
	X509_ALGOR *scheme = NULL, *kalg = NULL, *ret = NULL;
	int alg_nid, keylen;
	EVP_CIPHER_CTX ctx;
	unsigned char iv[EVP_MAX_IV_LENGTH];
	PBE2PARAM *pbe2 = NULL;
	ASN1_OBJECT *obj;

	alg_nid = EVP_CIPHER_type(cipher);
	if(alg_nid == NID_undef) {
		ASN1err(ASN1_F_PKCS5_PBE2_SET_IV,
				ASN1_R_CIPHER_HAS_NO_OBJECT_IDENTIFIER);
		goto err;
	}
	obj = OBJ_nid2obj(alg_nid);

	if(!(pbe2 = PBE2PARAM_new())) goto merr;


	scheme = pbe2->encryption;

	scheme->algorithm = obj;
	if(!(scheme->parameter = ASN1_TYPE_new())) goto merr;


	if (EVP_CIPHER_iv_length(cipher))
		{
		if (aiv)
			memcpy(iv, aiv, EVP_CIPHER_iv_length(cipher));
		else if (RAND_pseudo_bytes(iv, EVP_CIPHER_iv_length(cipher)) < 0)
  			goto err;
		}

	EVP_CIPHER_CTX_init(&ctx);


	if (!EVP_CipherInit_ex(&ctx, cipher, NULL, NULL, iv, 0))
		goto err;
	if(EVP_CIPHER_param_to_asn1(&ctx, scheme->parameter) < 0) {
		ASN1err(ASN1_F_PKCS5_PBE2_SET_IV,
					ASN1_R_ERROR_SETTING_CIPHER_PARAMS);
		EVP_CIPHER_CTX_cleanup(&ctx);
		goto err;
	}


	if ((prf_nid == -1) &&
	EVP_CIPHER_CTX_ctrl(&ctx, EVP_CTRL_PBE_PRF_NID, 0, &prf_nid) <= 0)
		{
		ERR_clear_error();
		prf_nid = NID_hmacWithSHA1;
		}
	EVP_CIPHER_CTX_cleanup(&ctx);


	if(alg_nid == NID_rc2_cbc)
		keylen = EVP_CIPHER_key_length(cipher);
	else
		keylen = -1;


	X509_ALGOR_free(pbe2->keyfunc);

	pbe2->keyfunc = PKCS5_pbkdf2_set(iter, salt, saltlen, prf_nid, keylen);

	if (!pbe2->keyfunc)
		goto merr;


	if(!(ret = X509_ALGOR_new())) goto merr;
	if(!(ret->parameter = ASN1_TYPE_new())) goto merr;

	ret->algorithm = OBJ_nid2obj(NID_pbes2);


	if(!ASN1_item_pack(pbe2, ASN1_ITEM_rptr(PBE2PARAM),
				 &ret->parameter->value.sequence)) goto merr;
	ret->parameter->type = V_ASN1_SEQUENCE;

	PBE2PARAM_free(pbe2);
	pbe2 = NULL;

	return ret;

	merr:
	ASN1err(ASN1_F_PKCS5_PBE2_SET_IV,ERR_R_MALLOC_FAILURE);

	err:
	PBE2PARAM_free(pbe2);

	X509_ALGOR_free(kalg);
	X509_ALGOR_free(ret);

	return NULL;

}
