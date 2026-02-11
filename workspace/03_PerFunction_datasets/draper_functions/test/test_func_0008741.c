bifrdm(bifcxdef *ctx, int argc)
{
    objnum    func;
    runsdef   val;
    voccxdef *voc = ctx->bifcxrun->runcxvoc;

    bifcntargs(ctx, 2, argc);
    func = runpopfn(ctx->bifcxrun);
    runpop(ctx->bifcxrun, &val);
    vocremfd(voc, voc->voccxdmn, func, (prpnum)0,
             &val, ERR_NODMN);
}
