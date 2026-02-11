convolve_setXformSpec (
    IP_XFORM_HANDLE hXform,
    DWORD_OR_PVOID  aXformInfo[])
{
    PCONV_INST g;
    int        i, n;

    HANDLE_TO_PTR (hXform, g);

    g->nRows    = aXformInfo[IP_CONVOLVE_NROWS  ].dword;
    g->nCols    = aXformInfo[IP_CONVOLVE_NCOLS  ].dword;
    g->iDivisor = aXformInfo[IP_CONVOLVE_DIVISOR].dword;

    INSURE ((g->nRows&1)!=0 && g->nRows>0 && g->nRows<=IP_CONVOLVE_MAXSIZE);
    INSURE ((g->nCols&1)!=0 && g->nCols>0 && g->nCols<=IP_CONVOLVE_MAXSIZE);
    INSURE (g->iDivisor != 0);
    INSURE (aXformInfo[IP_CONVOLVE_MATRIX].pvoid != 0);

    n = g->nRows * g->nCols;
    for (i=0; i<n; i++)
        g->matrix[i] = ((int*)(aXformInfo[IP_CONVOLVE_MATRIX].pvoid))[i];

    return IP_DONE;

    fatal_error:
    return IP_FATAL_ERROR;
}
