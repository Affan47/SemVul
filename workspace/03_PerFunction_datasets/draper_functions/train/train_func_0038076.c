pixCompareGray(PIX        *pix1,
               PIX        *pix2,
               l_int32     comptype,
               l_int32     plottype,
               l_int32    *psame,
               l_float32  *pdiff,
               l_float32  *prmsdiff,
               PIX       **ppixdiff)
{
l_int32  first, last;
GPLOT   *gplot;
NUMA    *na, *nac;
PIX     *pixt;

    PROCNAME("pixCompareGray");

    if (ppixdiff) *ppixdiff = NULL;
    if (!pix1 || pixGetDepth(pix1) != 8)
        return ERROR_INT("pix1 not defined or not 8 bpp", procName, 1);
    if (!pix2 || pixGetDepth(pix2) != 8)
        return ERROR_INT("pix2 not defined or not 8 bpp", procName, 1);
    if (pixGetColormap(pix1) || pixGetColormap(pix2))
        return ERROR_INT("pix1 and/or pix2 are colormapped", procName, 1);
    if (comptype != L_COMPARE_SUBTRACT && comptype != L_COMPARE_ABS_DIFF)
        return ERROR_INT("invalid comptype", procName, 1);
    if (plottype > NUM_GPLOT_OUTPUTS)
        return ERROR_INT("invalid plottype", procName, 1);

    if (comptype == L_COMPARE_SUBTRACT)
        pixt = pixSubtractGray(NULL, pix1, pix2);
    else
        pixt = pixAbsDifference(pix1, pix2);

    if (psame)
        pixZero(pixt, psame);

    if (pdiff)
        pixGetAverageMasked(pixt, NULL, 0, 0, 1, L_MEAN_ABSVAL, pdiff);

    if (plottype) {
        na = pixGetGrayHistogram(pixt, 1);
        numaGetNonzeroRange(na, TINY, &first, &last);
        nac = numaClipToInterval(na, 0, last);
        gplot = gplotCreate("/tmp/junkgrayroot", plottype,
                            "Pixel Difference Histogram", "diff val",
                            "number of pixels");
        gplotAddPlot(gplot, NULL, nac, GPLOT_LINES, "gray");
        gplotMakeOutput(gplot);
        gplotDestroy(&gplot);
        numaDestroy(&na);
        numaDestroy(&nac);
    }

    if (ppixdiff)
        *ppixdiff = pixCopy(NULL, pixt);

    if (prmsdiff) {
        if (comptype == L_COMPARE_SUBTRACT) {
            pixDestroy(&pixt);
            pixt = pixAbsDifference(pix1, pix2);
        }
        pixGetAverageMasked(pixt, NULL, 0, 0, 1, L_ROOT_MEAN_SQUARE, prmsdiff);
    }

    pixDestroy(&pixt);
    return 0;
}
