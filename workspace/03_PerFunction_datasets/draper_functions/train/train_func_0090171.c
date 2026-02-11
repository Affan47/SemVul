decrypt_token(struct webauth_context *ctx, const unsigned char *input,
              size_t length, unsigned char *output, size_t *output_len,
              const struct webauth_key *key)
{
    unsigned char computed_hmac[T_HMAC_S];
    size_t needed, plen, i;
    int s;
    unsigned char *hmac;
    AES_KEY aes_key;


    needed = T_HINT_S + T_NONCE_S + T_HMAC_S;
    if (length < needed + needed % AES_BLOCK_SIZE) {
        wai_error_set(ctx, WA_ERR_CORRUPT, "token too short");
        return WA_ERR_CORRUPT;
    }


    s = AES_set_decrypt_key(key->data, key->length * 8, &aes_key);
    if (s != 0) {
        s = WA_ERR_BAD_KEY;
        return openssl_error(ctx, s, "cannot set encryption key");
    }


    AES_cbc_encrypt(input + T_NONCE_O, output + T_NONCE_O, length - T_HINT_S,
                    &aes_key, aes_ivec, AES_DECRYPT);


    hmac = HMAC(EVP_sha1(), key->data, key->length, output + T_ATTR_O,
                length - T_ATTR_O, computed_hmac, NULL);
    if (hmac == NULL)
        return openssl_error(ctx, WA_ERR_CORRUPT, "cannot compute HMAC");
    if (memcmp(output + T_HMAC_O, computed_hmac, T_HMAC_S) != 0) {
        wai_error_set(ctx, WA_ERR_BAD_HMAC, NULL);
        return WA_ERR_BAD_HMAC;
    }


    plen = output[length - 1];
    if (plen > AES_BLOCK_SIZE || plen > length) {
        wai_error_set(ctx, WA_ERR_CORRUPT, "token padding corrupt");
        return WA_ERR_CORRUPT;
    }
    for (i = length - plen; i < length - 1; i++)
        if (output[i] != plen) {
            wai_error_set(ctx, WA_ERR_CORRUPT, "token padding corrupt");
            return WA_ERR_CORRUPT;
        }


    *output_len = length - T_ATTR_O - plen;
    memmove(output, output + T_ATTR_O, *output_len);
    return WA_ERR_NONE;
}
