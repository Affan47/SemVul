pixModifySaturation(PIX       *pixd,
                    PIX       *pixs,
                    l_float32  fract)
{
l_int32    w, h, d, i, j, wpl;
l_int32    rval, gval, bval, hval, sval, vval;
l_uint32  *data, *line;

    PROCNAME("pixModifySaturation");

    if (!pixs)
        return (PIX *)ERROR_PTR("pixs not defined", procName, NULL);
    pixGetDimensions(pixs, &w, &h, &d);
    if (d != 32)
        return (PIX *)ERROR_PTR("pixs not 32 bpp", procName, NULL);
    if (L_ABS(fract) > 1.0)
        return (PIX *)ERROR_PTR("fract not in [-1.0 ... 1.0]", procName, NULL);

    pixd = pixCopy(pixd, pixs);
    if (fract == 0.0) {
        L_WARNING("no change requested in saturation", procName);
        return pixd;
    }

    data = pixGetData(pixd);
    wpl = pixGetWpl(pixd);
    for (i = 0; i < h; i++) {
        line = data + i * wpl;
        for (j = 0; j < w; j++) {
            extractRGBValues(line[j], &rval, &gval, &bval);
            convertRGBToHSV(rval, gval, bval, &hval, &sval, &vval);
            if (fract < 0.0)
                sval = (l_int32)(sval * (1.0 + fract));
            else
                sval = (l_int32)(sval + fract * (255 - sval));
            convertHSVToRGB(hval, sval, vval, &rval, &gval, &bval);
            composeRGBPixel(rval, gval, bval, line + j);
        }
    }

    return pixd;
}
