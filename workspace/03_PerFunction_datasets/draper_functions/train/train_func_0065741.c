bifadw(bifcxdef *ctx, int argc)
{
    uchar    *wrd;
    objnum    objn;
    prpnum    prpn;
    vocidef  *voci;
    int       classflg;
    voccxdef *voc = ctx->bifcxrun->runcxvoc;

    bifcntargs(ctx, 3, argc);


    objn = runpopobj(ctx->bifcxrun);
    prpn = runpopprp(ctx->bifcxrun);
    wrd = runpopstr(ctx->bifcxrun);


    if (!prpisvoc(prpn))
        runsig1(ctx->bifcxrun, ERR_INVVBIF, ERRTSTR, "addword");


    voci = vocinh(voc, objn);

    classflg = VOCFNEW;
    if (voci->vociflg & VOCIFCLASS) classflg |= VOCFCLASS;


    vocadd(voc, prpn, objn, classflg, (char *)wrd);


    vocdusave_addwrd(voc, objn, prpn, classflg, (char *)wrd);
}
