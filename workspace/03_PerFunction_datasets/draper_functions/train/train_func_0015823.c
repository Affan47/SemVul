SHA512_DestroyContext(SHA512Context *ctx, PRBool freeit)
{
    memset(ctx, 0, sizeof *ctx);
    if (freeit) {
        PORT_Free(ctx);
    }
}
