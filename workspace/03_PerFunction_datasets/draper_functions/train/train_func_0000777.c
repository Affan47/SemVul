numaGetHistogramStats(NUMA       *nahisto,
                      l_float32   startx,
                      l_float32   deltax,
                      l_float32  *pxmean,
                      l_float32  *pxmedian,
                      l_float32  *pxmode,
                      l_float32  *pxvariance)
{
    PROCNAME("numaGetHistogramStats");

    if (pxmean) *pxmean = 0.0;
    if (pxmedian) *pxmedian = 0.0;
    if (pxmode) *pxmode = 0.0;
    if (pxvariance) *pxvariance = 0.0;
    if (!nahisto)
        return ERROR_INT("nahisto not defined", procName, 1);

    return numaGetHistogramStatsOnInterval(nahisto, startx, deltax, 0, 0,
                                           pxmean, pxmedian, pxmode,
                                           pxvariance);
}
