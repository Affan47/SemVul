PKCS5_v2_PBE_keyivgen(EVP_CIPHER_CTX *ctx, const char *pass, int passlen,
                         ASN1_TYPE *param, const EVP_CIPHER *c, const EVP_MD *md,
                         int en_de)
{
	const unsigned char *pbuf;
	int plen;
	PBE2PARAM *pbe2 = NULL;
	const EVP_CIPHER *cipher;

	int rv = 0;

	if (param == NULL || param->type != V_ASN1_SEQUENCE ||
	    param->value.sequence == NULL) {
		EVPerr(EVP_F_PKCS5_V2_PBE_KEYIVGEN,EVP_R_DECODE_ERROR);
		goto err;
	}

	pbuf = param->value.sequence->data;
	plen = param->value.sequence->length;
	if(!(pbe2 = d2i_PBE2PARAM(NULL, &pbuf, plen))) {
		EVPerr(EVP_F_PKCS5_V2_PBE_KEYIVGEN,EVP_R_DECODE_ERROR);
		goto err;
	}


	if(OBJ_obj2nid(pbe2->keyfunc->algorithm) != NID_id_pbkdf2) {
		EVPerr(EVP_F_PKCS5_V2_PBE_KEYIVGEN,
				EVP_R_UNSUPPORTED_KEY_DERIVATION_FUNCTION);
		goto err;
	}


	cipher = EVP_get_cipherbyobj(pbe2->encryption->algorithm);

	if(!cipher) {
		EVPerr(EVP_F_PKCS5_V2_PBE_KEYIVGEN,
						EVP_R_UNSUPPORTED_CIPHER);
		goto err;
	}


	if (!EVP_CipherInit_ex(ctx, cipher, NULL, NULL, NULL, en_de))
		goto err;
	if(EVP_CIPHER_asn1_to_param(ctx, pbe2->encryption->parameter) < 0) {
		EVPerr(EVP_F_PKCS5_V2_PBE_KEYIVGEN,
					EVP_R_CIPHER_PARAMETER_ERROR);
		goto err;
	}
	rv = PKCS5_v2_PBKDF2_keyivgen(ctx, pass, passlen,
					pbe2->keyfunc->parameter, c, md, en_de);
	err:
	PBE2PARAM_free(pbe2);
	return rv;
}
