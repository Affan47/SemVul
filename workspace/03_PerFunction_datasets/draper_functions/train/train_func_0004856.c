dewarpGetLineEndpoints(l_int32  h,
                       PTAA    *ptaa,
                       PTA    **pptal,
                       PTA    **pptar)
{
l_int32    i, n, npt, x, y;
l_float32  miny, maxy, ratio;
PTA       *pta, *ptal, *ptar;

    PROCNAME("dewarpGetLineEndpoints");

    if (!pptal || !pptar)
        return ERROR_INT("&ptal and &ptar not both defined", procName, 1);
    *pptal = *pptar = NULL;
    if (!ptaa)
        return ERROR_INT("ptaa undefined", procName, 1);

    n = ptaaGetCount(ptaa);
    ptal = ptaCreate(n);
    ptar = ptaCreate(n);
    for (i = 0; i < n; i++) {
        pta = ptaaGetPta(ptaa, i, L_CLONE);
        ptaGetIPt(pta, 0, &x, &y);
        ptaAddPt(ptal, y, x);
        npt = ptaGetCount(pta);
        ptaGetIPt(pta, npt - 1, &x, &y);
        ptaAddPt(ptar, y, x);
        ptaDestroy(&pta);
    }


    ptaGetRange(ptal, &miny, &maxy, NULL, NULL);
    ratio = (maxy - miny) / (l_float32)h;
    if (ratio < MIN_RATIO_LINES_TO_HEIGHT) {
        L_INFO("ratio lines to height, %f, too small\n", procName, ratio);
        ptaDestroy(&ptal);
        ptaDestroy(&ptar);
        return 1;
    }

    *pptal = ptal;
    *pptar = ptar;
    return 0;
}
