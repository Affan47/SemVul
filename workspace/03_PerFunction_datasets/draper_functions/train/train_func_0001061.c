crypto_aead_decrypt(
    unsigned char *m,unsigned long long *mlen,
    unsigned char *nsec,
    const unsigned char *c,unsigned long long clen,
    const unsigned char *ad,unsigned long long adlen,
    const unsigned char *npub,
    const unsigned char *k
)
{
    hs1siv_ctx_t ctx;
    (void)nsec;
    if (mlen) *mlen = clen-CRYPTO_ABYTES;
    hs1siv_subkeygen(&ctx, (void *)k, CRYPTO_KEYBYTES);
    return hs1siv_decrypt(&ctx, (void *)c, clen-CRYPTO_ABYTES, (void *)ad, adlen, (void *)npub, (void *)(c+clen-CRYPTO_ABYTES), m);
}
