ARCFOUR_subencrypt(krb5_context context,
		   struct _krb5_key_data *key,
		   void *data,
		   size_t len,
		   unsigned usage,
		   void *ivec)
{
    EVP_CIPHER_CTX ctx;
    struct _krb5_checksum_type *c = _krb5_find_checksum (CKSUMTYPE_RSA_MD5);
    Checksum k1_c, k2_c, k3_c, cksum;
    struct _krb5_key_data ke;
    krb5_keyblock kb;
    unsigned char t[4];
    unsigned char *cdata = data;
    unsigned char k1_c_data[16], k2_c_data[16], k3_c_data[16];
    krb5_error_code ret;

    t[0] = (usage >>  0) & 0xFF;
    t[1] = (usage >>  8) & 0xFF;
    t[2] = (usage >> 16) & 0xFF;
    t[3] = (usage >> 24) & 0xFF;

    k1_c.checksum.length = sizeof(k1_c_data);
    k1_c.checksum.data   = k1_c_data;

    ret = _krb5_internal_hmac(context, c, t, sizeof(t), 0, key, &k1_c);
    if (ret)
	krb5_abortx(context, "hmac failed");

    memcpy (k2_c_data, k1_c_data, sizeof(k1_c_data));

    k2_c.checksum.length = sizeof(k2_c_data);
    k2_c.checksum.data   = k2_c_data;

    ke.key = &kb;
    kb.keyvalue = k2_c.checksum;

    cksum.checksum.length = 16;
    cksum.checksum.data   = data;

    ret = _krb5_internal_hmac(context, c, cdata + 16, len - 16, 0, &ke, &cksum);
    if (ret)
	krb5_abortx(context, "hmac failed");

    ke.key = &kb;
    kb.keyvalue = k1_c.checksum;

    k3_c.checksum.length = sizeof(k3_c_data);
    k3_c.checksum.data   = k3_c_data;

    ret = _krb5_internal_hmac(context, c, data, 16, 0, &ke, &k3_c);
    if (ret)
	krb5_abortx(context, "hmac failed");

    EVP_CIPHER_CTX_init(&ctx);

    EVP_CipherInit_ex(&ctx, EVP_rc4(), NULL, k3_c.checksum.data, NULL, 1);
    EVP_Cipher(&ctx, cdata + 16, cdata + 16, len - 16);
    EVP_CIPHER_CTX_cleanup(&ctx);

    memset (k1_c_data, 0, sizeof(k1_c_data));
    memset (k2_c_data, 0, sizeof(k2_c_data));
    memset (k3_c_data, 0, sizeof(k3_c_data));
    return 0;
}
