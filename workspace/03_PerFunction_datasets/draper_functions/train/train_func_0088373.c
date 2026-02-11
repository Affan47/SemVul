numaHistogramGetValFromRank(NUMA       *na,
                            l_float32   rank,
                            l_float32  *prval)
{
l_int32    i, n;
l_float32  startval, binsize, rankcount, total, sum, fract, val;

    PROCNAME("numaHistogramGetValFromRank");

    if (!prval)
        return ERROR_INT("prval not defined", procName, 1);
    *prval = 0.0;
    if (!na)
        return ERROR_INT("na not defined", procName, 1);
    if (rank < 0.0) {
        L_WARNING("rank < 0; setting to 0.0", procName);
        rank = 0.0;
    }
    if (rank > 1.0) {
        L_WARNING("rank > 1.0; setting to 1.0", procName);
        rank = 1.0;
    }

    n = numaGetCount(na);
    numaGetXParameters(na, &startval, &binsize);
    numaGetSum(na, &total);
    rankcount = rank * total;
    sum = 0.0;
    for (i = 0; i < n; i++) {
        numaGetFValue(na, i, &val);
        if (sum + val >= rankcount)
            break;
        sum += val;
    }
    if (val <= 0.0)
        fract = 0.0;
    else
        fract = (rankcount - sum) / val;


    *prval = startval + binsize * ((l_float32)i + fract);


    return 0;
}
