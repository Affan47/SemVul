pixCreateRGBImage(PIX  *pixr,
                  PIX  *pixg,
                  PIX  *pixb)
{
l_int32  wr, wg, wb, hr, hg, hb, dr, dg, db;
PIX     *pixd;

    PROCNAME("pixCreateRGBImage");

    if (!pixr)
        return (PIX *)ERROR_PTR("pixr not defined", procName, NULL);
    if (!pixg)
        return (PIX *)ERROR_PTR("pixg not defined", procName, NULL);
    if (!pixb)
        return (PIX *)ERROR_PTR("pixb not defined", procName, NULL);
    pixGetDimensions(pixr, &wr, &hr, &dr);
    pixGetDimensions(pixg, &wg, &hg, &dg);
    pixGetDimensions(pixb, &wb, &hb, &db);
    if (dr != 8 || dg != 8 || db != 8)
        return (PIX *)ERROR_PTR("input pix not all 8 bpp", procName, NULL);
    if (wr != wg || wr != wb)
        return (PIX *)ERROR_PTR("widths not the same", procName, NULL);
    if (hr != hg || hr != hb)
        return (PIX *)ERROR_PTR("heights not the same", procName, NULL);

    if ((pixd = pixCreate(wr, hr, 32)) == NULL)
        return (PIX *)ERROR_PTR("pixd not made", procName, NULL);
    pixCopyResolution(pixd, pixr);
    pixSetRGBComponent(pixd, pixr, COLOR_RED);
    pixSetRGBComponent(pixd, pixg, COLOR_GREEN);
    pixSetRGBComponent(pixd, pixb, COLOR_BLUE);

    return pixd;
}
