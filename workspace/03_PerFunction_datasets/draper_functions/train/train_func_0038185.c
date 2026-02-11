fpixFlipTB(FPIX  *fpixd,
           FPIX  *fpixs)
{
l_int32     i, k, h, h2, wpl, bpl;
l_float32  *linet, *lineb, *data, *buffer;

    PROCNAME("fpixFlipTB");

    if (!fpixs)
        return (FPIX *)ERROR_PTR("fpixs not defined", procName, NULL);


    if ((fpixd = fpixCopy(fpixd, fpixs)) == NULL)
        return (FPIX *)ERROR_PTR("fpixd not made", procName, NULL);

    data = fpixGetData(fpixd);
    wpl = fpixGetWpl(fpixd);
    fpixGetDimensions(fpixd, NULL, &h);
    if ((buffer = (l_float32 *)CALLOC(wpl, sizeof(l_float32))) == NULL)
        return (FPIX *)ERROR_PTR("buffer not made", procName, NULL);
    h2 = h / 2;
    bpl = 4 * wpl;
    for (i = 0, k = h - 1; i < h2; i++, k--) {
        linet = data + i * wpl;
        lineb = data + k * wpl;
        memcpy(buffer, linet, bpl);
        memcpy(linet, lineb, bpl);
        memcpy(lineb, buffer, bpl);
    }
    FREE(buffer);
    return fpixd;
}
