dewarpaModelStats(L_DEWARPA  *dewa,
                  l_int32    *pnnone,
                  l_int32    *pnactual,
                  l_int32    *pnvalid,
                  l_int32    *pnref)
{
l_int32    i, n, pageno, nnone, nactual, nvalid, nref;
L_DEWARP  *dew;

    PROCNAME("dewarpaModelStats");

    if (!dewa)
        return ERROR_INT("dewa not defined", procName, 1);

    dewarpaListPages(dewa);
    n = numaGetCount(dewa->napages);
    nnone = nactual = nvalid = nref = 0;
    for (i = 0; i < n; i++) {
        numaGetIValue(dewa->napages, i, &pageno);
        dew = dewarpaGetDewarp(dewa, pageno);
        if (!dew) {
            nnone++;
            continue;
        }
        if (dew->hasref == 1)
            nref++;
        if (dew->success == 1)
            nactual++;
        if (dewarpaTestForValidModel(dewa, dew))
            nvalid++;
    }

    if (pnnone) *pnnone = nnone;
    if (pnactual) *pnactual = nactual;
    if (pnvalid) *pnvalid = nvalid;
    if (pnref) *pnref = nref;
    return 0;
}
