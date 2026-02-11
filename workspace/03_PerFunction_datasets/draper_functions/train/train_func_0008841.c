pixaEqual(PIXA     *pixa1,
          PIXA     *pixa2,
          l_int32   maxdist,
          NUMA    **pnaindex,
          l_int32  *psame)
{
l_int32   i, j, n, same, sameboxa;
BOXA     *boxa1, *boxa2;
NUMA     *na;
PIX      *pix1, *pix2;

    PROCNAME("pixaEqual");

    if (pnaindex) *pnaindex = NULL;
    if (!psame)
        return ERROR_INT("&same not defined", procName, 1);
    *psame = 0;
    sameboxa = 0;
    na = NULL;
    if (!pixa1 || !pixa2)
        return ERROR_INT("pixa1 and pixa2 not both defined", procName, 1);
    n = pixaGetCount(pixa1);
    if (n != pixaGetCount(pixa2))
        return 0;
    boxa1 = pixaGetBoxa(pixa1, L_CLONE);
    boxa2 = pixaGetBoxa(pixa2, L_CLONE);
    if (!boxa1 && !boxa2)
        maxdist = 0;
    if (boxa1 && !boxa2) {
        boxaDestroy(&boxa1);
        return 0;
    }
    if (!boxa1 && boxa2) {
        boxaDestroy(&boxa2);
        return 0;
    }
    if (boxa1 && boxa2) {
        boxaEqual(boxa1, boxa2, maxdist, &na, &sameboxa);
        boxaDestroy(&boxa1);
        boxaDestroy(&boxa2);
        if (!sameboxa) {
            numaDestroy(&na);
            return 0;
        }
    }

    for (i = 0; i < n; i++) {
        pix1 = pixaGetPix(pixa1, i, L_CLONE);
        if (na)
            numaGetIValue(na, i, &j);
        else
            j = i;
        pix2 = pixaGetPix(pixa2, j, L_CLONE);
        pixEqual(pix1, pix2, &same);
        pixDestroy(&pix1);
        pixDestroy(&pix2);
        if (!same) {
            numaDestroy(&na);
            return 0;
        }
    }

    *psame = 1;
    if (pnaindex)
        *pnaindex = na;
    else
        numaDestroy(&na);
    return 0;
}
