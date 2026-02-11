ARC4CryptBuf (HPDF_ARC4_Ctx_Rec  *ctx,
                           const HPDF_BYTE    *in,
                           HPDF_BYTE          *out,
                           HPDF_UINT          len)
{
    HPDF_UINT i;
    HPDF_UINT t;
    HPDF_BYTE K;

    HPDF_PTRACE((" ARC4CryptBuf\n"));

    for (i = 0; i < len; i++) {
        HPDF_BYTE tmp;

        ctx->idx1 = (HPDF_BYTE)((ctx->idx1 + 1) % 256);
        ctx->idx2 = (HPDF_BYTE)((ctx->idx2 +  ctx->state[ctx->idx1]) % 256);

        tmp = ctx->state[ctx->idx1];
        ctx->state[ctx->idx1] = ctx->state[ctx->idx2];
        ctx->state[ctx->idx2] = tmp;

        t = (ctx->state[ctx->idx1] + ctx->state[ctx->idx2]) % 256;
        K = ctx->state[t];

        out[i] = (HPDF_BYTE)(in[i] ^ K);
    }
}
