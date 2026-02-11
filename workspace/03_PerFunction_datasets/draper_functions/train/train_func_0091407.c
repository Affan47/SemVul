boxaJoin(BOXA    *boxad,
         BOXA    *boxas,
         l_int32  istart,
         l_int32  iend)
{
l_int32  ns, i;
BOX     *box;

    PROCNAME("boxaJoin");

    if (!boxad)
        return ERROR_INT("boxad not defined", procName, 1);
    if (!boxas)
        return ERROR_INT("boxas not defined", procName, 1);
    ns = boxaGetCount(boxas);
    if (istart < 0)
        istart = 0;
    if (istart >= ns)
        return ERROR_INT("istart out of bounds", procName, 1);
    if (iend <= 0)
        iend = ns - 1;
    if (iend >= ns)
        return ERROR_INT("iend out of bounds", procName, 1);
    if (istart > iend)
        return ERROR_INT("istart > iend; nothing to add", procName, 1);

    for (i = istart; i <= iend; i++) {
        box = boxaGetBox(boxas, i, L_CLONE);
        boxaAddBox(boxad, box, L_INSERT);
    }

    return 0;
}
