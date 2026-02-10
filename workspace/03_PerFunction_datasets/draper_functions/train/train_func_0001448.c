gplotAddPlot(GPLOT       *gplot,
             NUMA        *nax,
             NUMA        *nay,
             l_int32      plotstyle,
             const char  *plottitle)
{
char       buf[L_BUF_SIZE];
char       emptystring[] = "";
char      *datastr, *title;
l_int32    n, i;
l_float32  valx, valy, startx, delx;
SARRAY    *sa;

    PROCNAME("gplotAddPlot");

    if (!gplot)
        return ERROR_INT("gplot not defined", procName, 1);
    if (!nay)
        return ERROR_INT("nay not defined", procName, 1);
    if (plotstyle != GPLOT_LINES && plotstyle != GPLOT_POINTS &&
        plotstyle != GPLOT_IMPULSES && plotstyle != GPLOT_LINESPOINTS &&
        plotstyle != GPLOT_DOTS)
        return ERROR_INT("invalid plotstyle", procName, 1);

    n = numaGetCount(nay);
    numaGetXParameters(nay, &startx, &delx);
    if (nax) {
        if (n != numaGetCount(nax))
            return ERROR_INT("nax and nay sizes differ", procName, 1);
    }


    numaAddNumber(gplot->plotstyles, plotstyle);
    if (plottitle) {
        title = stringNew(plottitle);
        sarrayAddString(gplot->plottitles, title, L_INSERT);
    }
    else
        sarrayAddString(gplot->plottitles, emptystring, L_COPY);


    gplot->nplots++;
    snprintf(buf, L_BUF_SIZE, "%s.data.%d", gplot->rootname, gplot->nplots);
    sarrayAddString(gplot->datanames, buf, L_COPY);


    sa = sarrayCreate(n);
    for (i = 0; i < n; i++) {
        if (nax)
            numaGetFValue(nax, i, &valx);
        else
            valx = startx + i * delx;
        numaGetFValue(nay, i, &valy);
        snprintf(buf, L_BUF_SIZE, "%f %f\n", valx, valy);
        sarrayAddString(sa, buf, L_COPY);
    }
    datastr = sarrayToString(sa, 0);
    sarrayAddString(gplot->plotdata, datastr, L_INSERT);
    sarrayDestroy(&sa);

    return 0;
}
