boxaTransformOrdered(BOXA      *boxas,
                     l_int32    shiftx,
                     l_int32    shifty,
                     l_float32  scalex,
                     l_float32  scaley,
                     l_int32    xcen,
                     l_int32    ycen,
                     l_float32  angle,
                     l_int32    order)
{
l_int32  i, n;
BOX     *boxs, *boxd;
BOXA    *boxad;

    PROCNAME("boxaTransformOrdered");

    if (!boxas)
        return (BOXA *)ERROR_PTR("boxas not defined", procName, NULL);
    n = boxaGetCount(boxas);
    if ((boxad = boxaCreate(n)) == NULL)
        return (BOXA *)ERROR_PTR("boxad not made", procName, NULL);
    for (i = 0; i < n; i++) {
        if ((boxs = boxaGetBox(boxas, i, L_CLONE)) == NULL)
            return (BOXA *)ERROR_PTR("boxs not found", procName, NULL);
        boxd = boxTransformOrdered(boxs, shiftx, shifty, scalex, scaley,
                                   xcen, ycen, angle, order);
        boxDestroy(&boxs);
        boxaAddBox(boxad, boxd, L_INSERT);
    }

    return boxad;
}
