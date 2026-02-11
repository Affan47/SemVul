hs1siv_decrypt(hs1siv_ctx_t *ctx, void *c, unsigned cbytes, void *a, unsigned abytes, void *n, void *t, void *m)
{
    unsigned i, buflen = (abytes+15)/16*16 + (cbytes+15)/16*16 + 16;
    unsigned char *maybe_m = (unsigned char *)malloc(cbytes);
    unsigned char maybe_t[HS1_SIV_SIV_LEN];
    unsigned char *buf = (unsigned char *)malloc(cbytes+64);
    hs1(ctx, t, HS1_SIV_SIV_LEN, n, buf, cbytes+64);
    for (i=0; i<cbytes; i++)
        ((unsigned char *)maybe_m)[i] = ((unsigned char *)c)[i] ^ buf[64+i];
    free(buf);
    buf = (unsigned char *)malloc(buflen);
    memset(buf, 0, buflen);
    memcpy(buf, a, abytes);
    memcpy(buf+(abytes+15)/16*16, maybe_m, cbytes);
    write32le((uint32_t *)(buf+buflen-16), abytes);
    write32le((uint32_t *)(buf+buflen-8), cbytes);
    hs1(ctx, buf, buflen, n, maybe_t, HS1_SIV_SIV_LEN);
    free(buf);
    if (memcmp(t,maybe_t,HS1_SIV_SIV_LEN) == 0) {
        memcpy(m,maybe_m,cbytes);
        free(maybe_m);
        return 0;
    } else {
        free(maybe_m);
        return -1;
    }
}
