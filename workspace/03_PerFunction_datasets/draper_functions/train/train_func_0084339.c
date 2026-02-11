pixCorrelationScoreSimple(PIX        *pix1,
                          PIX        *pix2,
                          l_int32     area1,
                          l_int32     area2,
                          l_float32   delx,
                          l_float32   dely,
                          l_int32     maxdiffw,
                          l_int32     maxdiffh,
                          l_int32    *tab,
                          l_float32  *pscore)
{
l_int32  wi, hi, wt, ht, delw, delh, idelx, idely, count;
PIX     *pixt;

    PROCNAME("pixCorrelationScoreSimple");

    if (!pscore)
        return ERROR_INT("&score not defined", procName, 1);
    *pscore = 0.0;
    if (!pix1 || pixGetDepth(pix1) != 1)
        return ERROR_INT("pix1 not 1 bpp", procName, 1);
    if (!pix2 || pixGetDepth(pix2) != 1)
        return ERROR_INT("pix2 not 1 bpp", procName, 1);
    if (!tab)
        return ERROR_INT("tab not defined", procName, 1);
    if (!area1 || !area2)
        return ERROR_INT("areas must be > 0", procName, 1);


    pixGetDimensions(pix1, &wi, &hi, NULL);
    pixGetDimensions(pix2, &wt, &ht, NULL);
    delw = L_ABS(wi - wt);
    if (delw > maxdiffw)
        return 0;
    delh = L_ABS(hi - ht);
    if (delh > maxdiffh)
        return 0;


    if (delx >= 0)
        idelx = (l_int32)(delx + 0.5);
    else
        idelx = (l_int32)(delx - 0.5);
    if (dely >= 0)
        idely = (l_int32)(dely + 0.5);
    else
        idely = (l_int32)(dely - 0.5);


    pixt = pixCreateTemplate(pix1);
    pixRasterop(pixt, idelx, idely, wt, ht, PIX_SRC, pix2, 0, 0);
    pixRasterop(pixt, 0, 0, wi, hi, PIX_SRC & PIX_DST, pix1, 0, 0);
    pixCountPixels(pixt, &count, tab);
    pixDestroy(&pixt);

    *pscore = (l_float32)count * (l_float32)count /
               ((l_float32)area1 * (l_float32)area2);


    return 0;
}
