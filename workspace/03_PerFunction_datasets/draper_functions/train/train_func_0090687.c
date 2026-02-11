PKCS12_item_i2d_encrypt(X509_ALGOR *algor, const ASN1_ITEM *it,
				       const char *pass, int passlen,
				       void *obj, int zbuf)
{
	ASN1_OCTET_STRING *oct;
	unsigned char *in = NULL;
	int inlen;
	if (!(oct = M_ASN1_OCTET_STRING_new ())) {
		PKCS12err(PKCS12_F_PKCS12_ITEM_I2D_ENCRYPT,ERR_R_MALLOC_FAILURE);
		return NULL;
	}
	inlen = ASN1_item_i2d(obj, &in, it);
	if (!in) {
		PKCS12err(PKCS12_F_PKCS12_ITEM_I2D_ENCRYPT,PKCS12_R_ENCODE_ERROR);
		return NULL;
	}
	if (!PKCS12_pbe_crypt(algor, pass, passlen, in, inlen, &oct->data,
				 &oct->length, 1)) {
		PKCS12err(PKCS12_F_PKCS12_ITEM_I2D_ENCRYPT,PKCS12_R_ENCRYPT_ERROR);
		OPENSSL_free(in);
		return NULL;
	}
	if (zbuf) OPENSSL_cleanse(in, inlen);
	OPENSSL_free(in);
	return oct;
}
