pixGenerateMaskByBand32(PIX    *pixs,
                        l_uint32  refval,
                        l_int32   delm,
                        l_int32   delp)
{
l_int32    i, j, w, h, d, wpls, wpld;
l_int32    rref, gref, bref, rval, gval, bval;
l_uint32   pixel;
l_uint32  *datas, *datad, *lines, *lined;
PIX       *pixd;

    PROCNAME("pixGenerateMaskByBand32");

    if (!pixs)
        return (PIX *)ERROR_PTR("pixs not defined", procName, NULL);
    pixGetDimensions(pixs, &w, &h, &d);
    if (d != 32)
        return (PIX *)ERROR_PTR("not 32 bpp", procName, NULL);
    if (delm < 0 || delp < 0)
        return (PIX *)ERROR_PTR("delm and delp must be >= 0", procName, NULL);

    extractRGBValues(refval, &rref, &gref, &bref);
    pixd = pixCreate(w, h, 1);
    pixCopyResolution(pixd, pixs);
    datas = pixGetData(pixs);
    wpls = pixGetWpl(pixs);
    datad = pixGetData(pixd);
    wpld = pixGetWpl(pixd);
    for (i = 0; i < h; i++) {
        lines = datas + i * wpls;
        lined = datad + i * wpld;
        for (j = 0; j < w; j++) {
            pixel = lines[j];
            rval = (pixel >> L_RED_SHIFT) & 0xff;
            if (rval < rref - delm || rval > rref + delp)
                continue;
            gval = (pixel >> L_GREEN_SHIFT) & 0xff;
            if (gval < gref - delm || gval > gref + delp)
                continue;
            bval = (pixel >> L_BLUE_SHIFT) & 0xff;
            if (bval < bref - delm || bval > bref + delp)
                continue;
            SET_DATA_BIT(lined, j);
        }
    }

    return pixd;
}
