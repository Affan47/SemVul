numaGetPeakCentroids(NUMA  *nahist,
                     NUMA  *narange)
{
l_int32    i, j, nh, nr, low, high;
l_float32  cent, sum, val;
NUMA      *nad;

    PROCNAME("numaGetPeakCentroids");

    if (!nahist)
        return (NUMA *)ERROR_PTR("nahist not defined", procName, NULL);
    if (!narange)
        return (NUMA *)ERROR_PTR("narange not defined", procName, NULL);
    nh = numaGetCount(nahist);
    nr = numaGetCount(narange) / 2;

    nad = numaCreate(4);
    for (i = 0; i < nr; i++) {
        numaGetIValue(narange, 2 * i, &low);
        numaGetIValue(narange, 2 * i + 1, &high);
        cent = 0.0;
        sum = 0.0;
        for (j = low; j <= high; j++) {
            numaGetFValue(nahist, j, &val);
            cent += j * val;
            sum += val;
        }
        numaAddNumber(nad, cent / sum);
    }

    return nad;
}
