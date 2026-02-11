bifskt(bifcxdef *ctx, int argc)
{
    int turncnt;

    bifcntargs(ctx, 1, argc);
    turncnt = runpopnum(ctx->bifcxrun);
    if (turncnt < 1)
        runsig1(ctx->bifcxrun, ERR_INVVBIF, ERRTSTR, "skipturn");
    vocturn(ctx->bifcxrun->runcxvoc, turncnt, FALSE);
}
