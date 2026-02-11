pixFindDifferentialSquareSum(PIX        *pixs,
                             l_float32  *psum)
{
l_int32    i, n;
l_int32    w, h, skiph, skip, nskip;
l_float32  val1, val2, diff, sum;
NUMA      *na;

    PROCNAME("pixFindDifferentialSquareSum");

    if (!pixs)
        return ERROR_INT("pixs not defined", procName, 1);


    if ((na = pixCountPixelsByRow(pixs, NULL)) == NULL)
        return ERROR_INT("na not made", procName, 1);


    w = pixGetWidth(pixs);
    h = pixGetHeight(pixs);
    skiph = (l_int32)(0.05 * w);
    skip = L_MIN(h / 10, skiph);
    nskip = L_MAX(skip / 2, 1);


    n = numaGetCount(na);
    sum = 0.0;
    for (i = nskip; i < n - nskip; i++) {
        numaGetFValue(na, i - 1, &val1);
        numaGetFValue(na, i, &val2);
        diff = val2 - val1;
        sum += diff * diff;
    }
    numaDestroy(&na);
    *psum = sum;
    return 0;
}
