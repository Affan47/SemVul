_krb5_des_verify(krb5_context context,
		 const EVP_MD *evp_md,
		 struct _krb5_key_data *key,
		 const void *data,
		 size_t len,
		 Checksum *C)
{
    struct _krb5_evp_schedule *ctx = key->schedule->data;
    EVP_MD_CTX *m;
    unsigned char tmp[24];
    unsigned char res[16];
    DES_cblock ivec;
    krb5_error_code ret = 0;

    m = EVP_MD_CTX_create();
    if (m == NULL)
	return krb5_enomem(context);

    memset(&ivec, 0, sizeof(ivec));
    EVP_CipherInit_ex(&ctx->dctx, NULL, NULL, NULL, (void *)&ivec, -1);
    EVP_Cipher(&ctx->dctx, tmp, C->checksum.data, 24);

    EVP_DigestInit_ex(m, evp_md, NULL);
    EVP_DigestUpdate(m, tmp, 8);
    EVP_DigestUpdate(m, data, len);
    EVP_DigestFinal_ex (m, res, NULL);
    EVP_MD_CTX_destroy(m);
    if(ct_memcmp(res, tmp + 8, sizeof(res)) != 0) {
	krb5_clear_error_message (context);
	ret = KRB5KRB_AP_ERR_BAD_INTEGRITY;
    }
    memset(tmp, 0, sizeof(tmp));
    memset(res, 0, sizeof(res));
    return ret;
}
