aes128_init(void *ctx_, const uint8_t *key)
{
    aes_context *ctx = ctx_;
    unsigned int i;
    uint32_t *RK;

    ctx->nr = 10;
    ctx->rk = RK = ctx->buf;

    for (i = 0; i < 4; i++)
        GET_UINT32_LE(RK[i], key, i*4);

    for (i = 0; i < 10; i++, RK += 4)
    {
        RK[4] = RK[0] ^ RCON[i] ^
            ((uint32_t) FSb[(RK[3] >> 8) & 0xFF]) ^
            ((uint32_t) FSb[(RK[3] >> 16) & 0xFF] << 8) ^
            ((uint32_t) FSb[(RK[3] >> 24) & 0xFF] << 16) ^
            ((uint32_t) FSb[(RK[3]) & 0xFF] << 24);

        RK[5] = RK[1] ^ RK[4];
        RK[6] = RK[2] ^ RK[5];
        RK[7] = RK[3] ^ RK[6];
    }
}
