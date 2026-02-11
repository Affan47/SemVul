_krb5_des_checksum(krb5_context context,
		   const EVP_MD *evp_md,
		   struct _krb5_key_data *key,
		   const void *data,
		   size_t len,
		   Checksum *cksum)
{
    struct _krb5_evp_schedule *ctx = key->schedule->data;
    EVP_MD_CTX *m;
    DES_cblock ivec;
    unsigned char *p = cksum->checksum.data;

    krb5_generate_random_block(p, 8);

    m = EVP_MD_CTX_create();
    if (m == NULL)
	return krb5_enomem(context);

    EVP_DigestInit_ex(m, evp_md, NULL);
    EVP_DigestUpdate(m, p, 8);
    EVP_DigestUpdate(m, data, len);
    EVP_DigestFinal_ex (m, p + 8, NULL);
    EVP_MD_CTX_destroy(m);
    memset (&ivec, 0, sizeof(ivec));
    EVP_CipherInit_ex(&ctx->ectx, NULL, NULL, NULL, (void *)&ivec, -1);
    EVP_Cipher(&ctx->ectx, p, p, 24);

    return 0;
}
