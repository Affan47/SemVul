gen_publickey_from_dsa(LIBSSH2_SESSION* session, DSA *dsa,
                       size_t *key_len)
{
    int            p_bytes, q_bytes, g_bytes, k_bytes;
    unsigned long  len;
    unsigned char* key;
    unsigned char* p;

    p_bytes = BN_num_bytes(dsa->p) + 1;
    q_bytes = BN_num_bytes(dsa->q) + 1;
    g_bytes = BN_num_bytes(dsa->g) + 1;
    k_bytes = BN_num_bytes(dsa->pub_key) + 1;


    len = 4 + 7 + 4 + p_bytes + 4 + q_bytes + 4 + g_bytes + 4 + k_bytes;

    key = LIBSSH2_ALLOC(session, len);
    if (key == NULL) {
        return NULL;
    }


    p = key;

    _libssh2_htonu32(p, 7);
    p += 4;
    memcpy(p, "ssh-dss", 7);
    p += 7;

    p = write_bn(p, dsa->p, p_bytes);
    p = write_bn(p, dsa->q, q_bytes);
    p = write_bn(p, dsa->g, g_bytes);
    p = write_bn(p, dsa->pub_key, k_bytes);

    *key_len = (size_t)(p - key);
    return key;
}
