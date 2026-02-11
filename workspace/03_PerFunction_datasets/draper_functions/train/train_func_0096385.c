mcmalo0(mcmcxdef *cctx, ushort siz, mcmon *nump,
               mcmon clinum, int noclitrans)
{
    uchar     *ret;
    mcmcx1def *ctx = cctx->mcmcxgl;
    mcmon      glb;

    MCMCLICTX(cctx);
    MCMGLBCTX(ctx);


    if ((ret = mcmalo1(ctx, siz, &glb)) != 0)
        goto done;


    mcmgarb(ctx);


    for ( ;; )
    {

        if ((ret = mcmalo1(ctx, siz, &glb)) != 0)
            goto done;


        if (!mcmswap(ctx, siz))
            break;


        if ((ret = mcmalo1(ctx, siz, &glb)) != 0)
            goto done;


        mcmgarb(ctx);
    }


    if ((ret = mcmalo1(ctx, siz, &glb)) != 0)
        goto done;


    errsig(ctx->mcmcxerr, ERR_NOMEM1);
    NOTREACHEDV(uchar *);

done:
    if (noclitrans)
    {
        *nump = glb;
        return(ret);
    }


    if (clinum == MCMONINV)
    {

        mcmon **p;
        uint    i;
        mcmon   j;
        mcmon  *q;
        int     found = FALSE;
        int     unused = -1;

        for (i = 0, p = cctx->mcmcxmtb ; i < cctx->mcmcxmsz ; ++i, ++p)
        {
            if (*p)
            {
                for (j = 0, q = *p ; j < 256 ; ++j, ++q)
                {
                    if (*q == MCMONINV)
                    {
                        found = TRUE;
                        break;
                    }
                }
            }
            else if (unused == -1)
                unused = i;

            if (found) break;
        }

        if (found)
            clinum = (i << 8) + j;
        else if (unused != -1)
            clinum = (unused << 8);
        else
            errsig(ctx->mcmcxerr, ERR_CLIFULL);
    }


    mcmcliexp(cctx, clinum);


    if (mcmc2g(cctx, clinum) != MCMONINV)
        errsig(ctx->mcmcxerr, ERR_CLIUSE);

    cctx->mcmcxmtb[clinum >> 8][clinum & 255] = glb;
    if (nump) *nump = clinum;
    return(ret);
}
