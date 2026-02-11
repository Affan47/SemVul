crypto_stream_chacha20_ietf_ref_xor_ic(unsigned char *c, const unsigned char *m,
                                       unsigned long long mlen,
                                       const unsigned char *n, uint32_t ic,
                                       const unsigned char *k)
{
    struct chacha_ctx ctx;
    uint8_t           ic_bytes[4];

    if (!mlen) {
        return 0;
    }
    U32TO8_LITTLE(ic_bytes, ic);
    chacha_keysetup(&ctx, k);
    chacha_ietf_ivsetup(&ctx, n, ic_bytes);
    chacha_encrypt_bytes(&ctx, m, c, mlen);
    sodium_memzero(&ctx, sizeof ctx);
    sodium_memzero(ic_bytes, sizeof ic_bytes);

    return 0;
}
