PBKDF2(unsigned char **key, size_t dkey_len,
           unsigned char *pw, size_t pw_len,
           unsigned char *salt, size_t salt_len, unsigned int c)
{
    int i;
    unsigned int l = 0;

    unsigned char *dk = NULL;
    unsigned char T[SHA_DIGEST_LENGTH];
    size_t h_len = SHA_DIGEST_LENGTH;
    size_t remaining_bytes = dkey_len;

    if (!key || !dkey_len || !pw || !pw_len || !salt || !salt_len || !c )
        return -1;


    if ((dk = malloc(dkey_len)) == NULL) return -1;
    memset(dk, 0, dkey_len);
    memset(T, 0, sizeof(T));


    l = (dkey_len/h_len);
    if (dkey_len % h_len) {
        l++;
    }


    for (i = 0; i < l; i++) {
        if (PBKDF2_F(T, pw, pw_len, salt, salt_len, c, i) != 0)
            goto cleanup;

        if (remaining_bytes >= h_len) {
            memcpy(dk + (i * h_len), T, h_len);
            remaining_bytes -= h_len;
        } else {
            memcpy(dk + (i * h_len), T, remaining_bytes);
            remaining_bytes -= remaining_bytes;
        }
    }
    *key = dk;
    return 0;

cleanup:
    sfree(dk, dkey_len);
    return -1;
}
