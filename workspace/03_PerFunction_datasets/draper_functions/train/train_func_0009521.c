vocinialo(voccxdef *ctx, vocddef **what, int cnt)
{
    vocddef *p;

    *what = (vocddef *)mchalo(ctx->voccxerr,
                              (ushort)(cnt * sizeof(vocddef)), "vocinialo");


    for (p = *what ; cnt ; ++p, --cnt)
        p->vocdfn = MCMONINV;
}
