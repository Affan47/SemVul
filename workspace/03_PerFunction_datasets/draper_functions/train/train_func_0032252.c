boxaGetArea(BOXA     *boxa,
            l_int32  *parea)
{
l_int32  i, n, w, h;

    PROCNAME("boxaGetArea");

    if (!parea)
        return ERROR_INT("&area not defined", procName, 1);
    *parea = 0;
    if (!boxa)
        return ERROR_INT("boxa not defined", procName, 1);

    n = boxaGetCount(boxa);
    for (i = 0; i < n; i++) {
        boxaGetBoxGeometry(boxa, i, NULL, NULL, &w, &h);
        *parea += w * h;
    }
    return 0;
}
