pixaSelectWithIndicator(PIXA     *pixas,
                        NUMA     *na,
                        l_int32  *pchanged)
{
l_int32  i, n, nbox, ival, nsave;
BOX     *box;
PIX     *pixt;
PIXA    *pixad;

    PROCNAME("pixaSelectWithIndicator");

    if (!pixas)
        return (PIXA *)ERROR_PTR("pixas not defined", procName, NULL);
    if (!na)
        return (PIXA *)ERROR_PTR("na not defined", procName, NULL);

    nsave = 0;
    n = numaGetCount(na);
    for (i = 0; i < n; i++) {
        numaGetIValue(na, i, &ival);
        if (ival == 1) nsave++;
    }

    if (nsave == n) {
        if (pchanged) *pchanged = FALSE;
        return pixaCopy(pixas, L_CLONE);
    }
    if (pchanged) *pchanged = TRUE;
    pixad = pixaCreate(nsave);
    nbox = pixaGetBoxaCount(pixas);
    for (i = 0; i < n; i++) {
        numaGetIValue(na, i, &ival);
        if (ival == 0) continue;
        pixt = pixaGetPix(pixas, i, L_CLONE);
        pixaAddPix(pixad, pixt, L_INSERT);
        if (nbox == n) {
            box = pixaGetBox(pixas, i, L_CLONE);
            pixaAddBox(pixad, box, L_INSERT);
        }
    }

    return pixad;
}
