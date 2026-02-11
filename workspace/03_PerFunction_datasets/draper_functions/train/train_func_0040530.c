pixSplitDistributionFgBg(PIX       *pixs,
                         l_float32  scorefract,
                         l_int32    factor,
                         l_int32   *pthresh,
                         l_int32   *pfgval,
                         l_int32   *pbgval,
                         l_int32    debugflag)
{
l_int32    thresh;
l_float32  avefg, avebg, maxnum;
GPLOT     *gplot;
NUMA      *na, *nascore, *nax, *nay;
PIX       *pixg;

    PROCNAME("pixSplitDistributionFgBg");

    if (pthresh) *pthresh = 0;
    if (pfgval) *pfgval = 0;
    if (pbgval) *pbgval = 0;
    if (!pixs)
        return ERROR_INT("pixs not defined", procName, 1);


    pixg = pixConvertTo8BySampling(pixs, factor, 0);


    na = pixGetGrayHistogram(pixg, 1);
    if (debugflag) {
        numaSplitDistribution(na, scorefract, &thresh, &avefg, &avebg,
                              NULL, NULL, &nascore);
        numaDestroy(&nascore);
    }
    else
        numaSplitDistribution(na, scorefract, &thresh, &avefg, &avebg,
                              NULL, NULL, NULL);

    if (pthresh) *pthresh = thresh;
    if (pfgval) *pfgval = (l_int32)(avefg + 0.5);
    if (pbgval) *pbgval = (l_int32)(avebg + 0.5);

    if (debugflag) {
        gplot = gplotCreate("junk_histplot", GPLOT_X11, "Histogram",
                            "Grayscale value", "Number of pixels");
        gplotAddPlot(gplot, NULL, na, GPLOT_LINES, NULL);
        nax = numaMakeConstant(thresh, 2);
        numaGetMax(na, &maxnum, NULL);
        nay = numaMakeConstant(0, 2);
        numaReplaceNumber(nay, 1, (l_int32)(0.5 * maxnum));
        gplotAddPlot(gplot, nax, nay, GPLOT_LINES, NULL);
        gplotMakeOutput(gplot);
        gplotDestroy(&gplot);
        numaDestroy(&nax);
        numaDestroy(&nay);
    }

    pixDestroy(&pixg);
    numaDestroy(&na);
    return 0;
}
