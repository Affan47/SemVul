pixThinGeneral(PIX     *pixs,
               l_int32  type,
               SELA    *sela,
               l_int32  maxiters)
{
l_int32  i, j, r, nsels, same;
PIXA    *pixahmt;
PIX    **pixhmt;
PIX     *pixd, *pixt;
SEL     *sel, *selr;

    PROCNAME("pixThinGeneral");

    if (!pixs)
        return (PIX *)ERROR_PTR("pixs not defined", procName, NULL);
    if (pixGetDepth(pixs) != 1)
        return (PIX *)ERROR_PTR("pixs not 1 bpp", procName, NULL);
    if (type != L_THIN_FG && type != L_THIN_BG)
        return (PIX *)ERROR_PTR("invalid fg/bg type", procName, NULL);
    if (!sela)
        return (PIX *)ERROR_PTR("sela not defined", procName, NULL);
    if (maxiters == 0) maxiters = 10000;


    nsels = selaGetCount(sela);
    pixahmt = pixaCreate(nsels);
    for (i = 0; i < nsels; i++) {
        pixt = pixCreateTemplate(pixs);
        pixaAddPix(pixahmt, pixt, L_INSERT);
    }
    pixhmt = pixaGetPixArray(pixahmt);
    if (!pixhmt)
        return (PIX *)ERROR_PTR("pixhmt array not made", procName, NULL);

#if  DEBUG_SELS
    pixt = selaDisplayInPix(sela, 35, 3, 15, 4);
    pixDisplayWithTitle(pixt, 100, 100, "allsels", 1);
    pixDestroy(&pixt);
#endif


    if (type == L_THIN_FG)
        pixd = pixCopy(NULL, pixs);
    else
        pixd = pixInvert(NULL, pixs);


    for (i = 0; i < maxiters; i++) {
        pixt = pixCopy(NULL, pixd);
        for (r = 0; r < 4; r++) {
            for (j = 0; j < nsels; j++) {
                sel = selaGetSel(sela, j);
                selr = selRotateOrth(sel, r);
                pixHMT(pixhmt[j], pixd, selr);
                selDestroy(&selr);
                if (j > 0)
                    pixOr(pixhmt[0], pixhmt[0], pixhmt[j]);
            }
            pixSubtract(pixd, pixd, pixhmt[0]);
        }
        pixEqual(pixd, pixt, &same);
        pixDestroy(&pixt);
        if (same) {
            L_INFO("%d iterations to completion\n", procName, i);
            break;
        }
    }

    if (type == L_THIN_BG)
        pixInvert(pixd, pixd);

    pixaDestroy(&pixahmt);
    return pixd;
}
