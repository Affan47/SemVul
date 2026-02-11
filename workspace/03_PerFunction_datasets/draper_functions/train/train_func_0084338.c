dewarpaCreateFromPixacomp(PIXAC   *pixac,
                          l_int32  sampling,
                          l_int32  minlines,
                          l_int32  maxdist)
{
l_int32     i, nptrs, pageno;
L_DEWARP   *dew;
L_DEWARPA  *dewa;
PIX        *pixt;

    PROCNAME("dewarpaCreateFromPixacomp");

    if (!pixac)
        return (L_DEWARPA *)ERROR_PTR("pixac not defined", procName, NULL);

    nptrs = pixacompGetCount(pixac);
    if ((dewa = dewarpaCreate(pixacompGetOffset(pixac) + nptrs,
                              sampling, 1, minlines, maxdist)) == NULL)
        return (L_DEWARPA *)ERROR_PTR("dewa not made", procName, NULL);

    for (i = 0; i < nptrs; i++) {
        pageno = pixacompGetOffset(pixac) + i;
        pixt = pixacompGetPix(pixac, pageno);
        if (pixt && (pixGetWidth(pixt) > 1)) {
            dew = dewarpCreate(pixt, pageno);
            pixDestroy(&pixt);
            if (!dew) {
                ERROR_INT("unable to make dew!", procName, 1);
                continue;
            }


            dewarpaInsertDewarp(dewa, dew);


            dewarpBuildModel(dew, NULL);
            if (!dew->success) {
                dewarpaDestroyDewarp(dewa, pageno);
                L_ERROR_INT("unable to build model for page %d", procName, i);
                continue;
            }

            dewarpMinimize(dew);
        }
        pixDestroy(&pixt);
    }
    dewarpaInsertRefModels(dewa, 0);

    return dewa;
}
