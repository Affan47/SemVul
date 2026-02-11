pixReadBarcodes(PIXA     *pixa,
                l_int32   format,
                l_int32   method,
                SARRAY  **psaw,
                l_int32   debugflag)
{
char      *barstr, *data;
l_int32    i, j, n, nbars, ival;
NUMA      *na;
PIX       *pixt;
SARRAY    *saw, *sad;

    PROCNAME("pixReadBarcodes");

    if (psaw) *psaw = NULL;
    if (!pixa)
        return (SARRAY *)ERROR_PTR("pixa not defined", procName, NULL);
    if (format != L_BF_ANY && !barcodeFormatIsSupported(format))
        return (SARRAY *)ERROR_PTR("unsupported format", procName, NULL);
    if (method != L_USE_WIDTHS && method != L_USE_WINDOWS)
        return (SARRAY *)ERROR_PTR("invalid method", procName, NULL);

    n = pixaGetCount(pixa);
    saw = sarrayCreate(n);
    sad = sarrayCreate(n);
    for (i = 0; i < n; i++) {

        pixt = pixaGetPix(pixa, i, L_CLONE);
        na = pixReadBarcodeWidths(pixt, method, debugflag);
        pixDestroy(&pixt);
        if (!na) {
	    ERROR_INT("valid barcode widths not returned", procName, 1);
            continue;
	}


        nbars = numaGetCount(na);
        barstr = (char *)CALLOC(nbars + 1, sizeof(char));
        for (j = 0; j < nbars; j++) {
            numaGetIValue(na, j, &ival);
            barstr[j] = 0x30 + ival;
        }
        sarrayAddString(saw, barstr, L_INSERT);
        numaDestroy(&na);


        data = barcodeDispatchDecoder(barstr, format, debugflag);
        if (!data) {
	    ERROR_INT("barcode not decoded", procName, 1);
            sarrayAddString(sad, "", L_COPY);
            continue;
	}
        sarrayAddString(sad, data, L_INSERT);
    }


    if (sarrayGetCount(saw) == 0) {
        sarrayDestroy(&saw);
        sarrayDestroy(&sad);
        return (SARRAY *)ERROR_PTR("no valid barcode data", procName, NULL);
    }

    if (psaw)
        *psaw = saw;
    else
        sarrayDestroy(&saw);

    return sad;
}
