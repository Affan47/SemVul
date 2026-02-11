vocsetfd(voccxdef *ctx, vocddef *what, objnum func, prpnum prop,
              uint tm, runsdef *val, int err)
{
    int      slots;

    if (what == ctx->voccxdmn)
        slots = ctx->voccxdmc;
    else if (what == ctx->voccxalm)
        slots = ctx->voccxalc;
    else if (what == ctx->voccxfus)
        slots = ctx->voccxfuc;
    else
        errsig(ctx->voccxerr, ERR_BADSETF);


    for ( ; slots ; ++what, --slots)
    {
        if (what->vocdfn == MCMONINV)
        {

            vocdusav(ctx, what);


            what->vocdfn = func;
            if (val != 0)
                OSCPYSTRUCT(what->vocdarg, *val);
            what->vocdprp = prop;
            what->vocdtim = tm;


            return;
        }
    }


    errsig(ctx->voccxerr, err);
}
