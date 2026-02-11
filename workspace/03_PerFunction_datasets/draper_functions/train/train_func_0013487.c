pixDisplayPta(PIX  *pixd,
              PIX  *pixs,
              PTA  *pta)
{
l_int32   i, n, x, y;
l_uint32  rpixel, gpixel, bpixel;

    PROCNAME("pixDisplayPta");

    if (!pixs)
        return (PIX *)ERROR_PTR("pixs not defined", procName, NULL);
    if (!pta)
        return (PIX *)ERROR_PTR("pta not defined", procName, NULL);
    if (pixd && (pixd != pixs || pixGetDepth(pixd) != 32))
        return (PIX *)ERROR_PTR("invalid pixd", procName, NULL);

    if (!pixd)
        pixd = pixConvertTo32(pixs);
    composeRGBPixel(255, 0, 0, &rpixel);
    composeRGBPixel(0, 255, 0, &gpixel);
    composeRGBPixel(0, 0, 255, &bpixel);

    n = ptaGetCount(pta);
    for (i = 0; i < n; i++) {
        ptaGetIPt(pta, i, &x, &y);
        if (i == 0)
            pixSetPixel(pixd, x, y, rpixel);
        else if (i < n - 1)
            pixSetPixel(pixd, x, y, gpixel);
        else
            pixSetPixel(pixd, x, y, bpixel);
    }

    return pixd;
}
