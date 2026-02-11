numaGetHistogramStatsOnInterval(NUMA       *nahisto,
                                l_float32   startx,
                                l_float32   deltax,
                                l_int32     ifirst,
                                l_int32     ilast,
                                l_float32  *pxmean,
                                l_float32  *pxmedian,
                                l_float32  *pxmode,
                                l_float32  *pxvariance)
{
l_int32    i, n, imax;
l_float32  sum, sumval, halfsum, moment, var, x, y, ymax;

    PROCNAME("numaGetHistogramStats");

    if (pxmean) *pxmean = 0.0;
    if (pxmedian) *pxmedian = 0.0;
    if (pxmode) *pxmode = 0.0;
    if (pxvariance) *pxvariance = 0.0;
    if (!nahisto)
        return ERROR_INT("nahisto not defined", procName, 1);
    if (!pxmean && !pxmedian && !pxmode && !pxvariance)
        return ERROR_INT("nothing to compute", procName, 1);

    n = numaGetCount(nahisto);
    if (ilast <= 0) ilast = n - 1;
    if (ifirst < 0) ifirst = 0;
    if (ifirst > ilast || ifirst > n - 1)
        return ERROR_INT("ifirst is too large", procName, 1);
    for (sum = 0.0, moment = 0.0, var = 0.0, i = ifirst; i <= ilast ; i++) {
        x = startx + i * deltax;
        numaGetFValue(nahisto, i, &y);
        sum += y;
        moment += x * y;
        var += x * x * y;
    }
    if (sum == 0.0)
        return ERROR_INT("sum is 0", procName, 1);

    if (pxmean)
        *pxmean = moment / sum;
    if (pxvariance)
        *pxvariance = var / sum - moment * moment / (sum * sum);

    if (pxmedian) {
        halfsum = sum / 2.0;
        for (sumval = 0.0, i = ifirst; i <= ilast; i++) {
            numaGetFValue(nahisto, i, &y);
            sumval += y;
            if (sumval >= halfsum) {
                *pxmedian = startx + i * deltax;
                break;
            }
        }
    }

    if (pxmode) {
        ymax = -1.0e10;
        for (i = ifirst; i <= ilast; i++) {
            numaGetFValue(nahisto, i, &y);
            if (y > ymax) {
                ymax = y;
                imax = i;
            }
        }
        *pxmode = startx + imax * deltax;
    }

    return 0;
}
