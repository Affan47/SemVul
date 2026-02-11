jbRankHaus(const char  *dirin,
           l_int32      size,
           l_float32    rank,
           l_int32      components,
           const char  *rootname,
           l_int32      firstpage,
           l_int32      npages,
           l_int32      renderflag)
{
char        filename[L_BUF_SIZE];
l_int32     nfiles, i, numpages;
JBDATA     *data;
JBCLASSER  *classer;
PIX        *pix;
PIXA       *pixa;
SARRAY     *safiles;

    PROCNAME("jbRankHaus");

    if (!dirin)
        return ERROR_INT("dirin not defined", procName, 1);
    if (!rootname)
        return ERROR_INT("rootname not defined", procName, 1);
    if (components != JB_CONN_COMPS && components != JB_CHARACTERS &&
        components != JB_WORDS)
        return ERROR_INT("components invalid", procName, 1);

    safiles = getSortedPathnamesInDirectory(dirin, NULL, firstpage, npages);
    nfiles = sarrayGetCount(safiles);


    classer = jbRankHausInit(components, 0, 0, size, rank);
    jbAddPages(classer, safiles);


    data = jbDataSave(classer);
    jbDataWrite(rootname, data);


    if (renderflag) {
        pixa = jbDataRender(data, FALSE);
        numpages = pixaGetCount(pixa);
        if (numpages != nfiles)
            fprintf(stderr, "numpages = %d, nfiles = %d, not equal!\n",
                    numpages, nfiles);
        for (i = 0; i < numpages; i++) {
            pix = pixaGetPix(pixa, i, L_CLONE);
            snprintf(filename, L_BUF_SIZE, "%s.%05d", rootname, i);
            fprintf(stderr, "filename: %s\n", filename);
            pixWrite(filename, pix, IFF_PNG);
            pixDestroy(&pix);
        }
        pixaDestroy(&pixa);
    }

    sarrayDestroy(&safiles);
    jbClasserDestroy(&classer);
    jbDataDestroy(&data);
    return 0;
}
