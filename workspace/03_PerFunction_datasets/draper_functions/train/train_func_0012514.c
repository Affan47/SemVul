pixConvertTo1(PIX     *pixs,
              l_int32  threshold)
{
l_int32   d, color0, color1, rval, gval, bval;
PIX      *pixg, *pixd;
PIXCMAP  *cmap;

    PROCNAME("pixConvertTo1");

    if (!pixs)
        return (PIX *)ERROR_PTR("pixs not defined", procName, NULL);
    d = pixGetDepth(pixs);
    if (d != 1 && d != 2 && d != 4 && d != 8 && d != 16 && d != 32)
        return (PIX *)ERROR_PTR("depth not {1,2,4,8,16,32}", procName, NULL);

    cmap = pixGetColormap(pixs);
    if (d == 1) {
        if (!cmap)
            return pixCopy(NULL, pixs);
        else {

            pixcmapGetColor(cmap, 0, &rval, &gval, &bval);
            color0 = rval + gval + bval;
            pixcmapGetColor(cmap, 1, &rval, &gval, &bval);
            color1 = rval + gval + bval;
            pixd = pixCopy(NULL, pixs);
            pixDestroyColormap(pixd);
            if (color1 > color0)
                pixInvert(pixd, pixd);
            return pixd;
        }
    }


    pixg = pixConvertTo8(pixs, FALSE);
    pixd = pixThresholdToBinary(pixg, threshold);
    pixDestroy(&pixg);
    return pixd;
}
