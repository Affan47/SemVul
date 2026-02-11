pixSubtractGray(PIX  *pixd,
                PIX  *pixs1,
                PIX  *pixs2)
{
l_int32    w, h, ws, hs, d, wpls, wpld;
l_uint32  *datas, *datad;

    PROCNAME("pixSubtractGray");

    if (!pixs1)
        return (PIX *)ERROR_PTR("pixs1 not defined", procName, pixd);
    if (!pixs2)
        return (PIX *)ERROR_PTR("pixs2 not defined", procName, pixd);
    if (pixs2 == pixs1)
        return (PIX *)ERROR_PTR("pixs2 and pixs1 must differ", procName, pixd);
    if (pixs2 == pixd)
        return (PIX *)ERROR_PTR("pixs2 and pixd must differ", procName, pixd);
    d = pixGetDepth(pixs1);
    if (d != 8 && d != 16 && d != 32)
        return (PIX *)ERROR_PTR("pix are not 8, 16 or 32 bpp", procName, pixd);
    if (pixGetDepth(pixs2) != d)
        return (PIX *)ERROR_PTR("depths differ (pixs1, pixs2)", procName, pixd);
    if (pixd && (pixGetDepth(pixd) != d))
        return (PIX *)ERROR_PTR("depths differ (pixs1, pixd)", procName, pixd);

    if (!pixSizesEqual(pixs1, pixs2))
        L_WARNING("pixs1 and pixs2 not equal in size", procName);
    if (pixd && !pixSizesEqual(pixs1, pixd))
        L_WARNING("pixs1 and pixd not equal in size", procName);

    if (pixs1 != pixd)
        pixd = pixCopy(pixd, pixs1);


    datas = pixGetData(pixs2);
    datad = pixGetData(pixd);
    wpls = pixGetWpl(pixs2);
    wpld = pixGetWpl(pixd);
    pixGetDimensions(pixs2, &ws, &hs, NULL);
    pixGetDimensions(pixd, &w, &h, NULL);
    w = L_MIN(ws, w);
    h = L_MIN(hs, h);
    subtractGrayLow(datad, w, h, d, wpld, datas, wpls);

    return pixd;
}
