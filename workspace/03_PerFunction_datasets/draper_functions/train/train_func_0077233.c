ccbaDisplayBorder(CCBORDA  *ccba)
{
l_int32  ncc, nb, n, i, j, k, x, y;
CCBORD  *ccb;
PIX     *pixd;
PTAA    *ptaa;
PTA     *pta;

    PROCNAME("ccbaDisplayBorder");

    if (!ccba)
        return (PIX *)ERROR_PTR("ccba not defined", procName, NULL);

    if ((pixd = pixCreate(ccba->w, ccba->h, 1)) == NULL)
        return (PIX *)ERROR_PTR("pixd not made", procName, NULL);
    ncc = ccbaGetCount(ccba);
    for (i = 0; i < ncc; i++) {
        ccb = ccbaGetCcb(ccba, i);
        if ((ptaa = ccb->global) == NULL) {
            L_WARNING("global pixel loc array not found", procName);
            continue;
        }
        nb = ptaaGetCount(ptaa);
        for (j = 0; j < nb; j++) {
            pta = ptaaGetPta(ptaa, j, L_CLONE);
            n = ptaGetCount(pta);
            for (k = 0; k < n; k++) {
                ptaGetIPt(pta, k, &x, &y);
                pixSetPixel(pixd, x, y, 1);
            }
            ptaDestroy(&pta);
        }
        ccbDestroy(&ccb);
    }

    return pixd;
}
