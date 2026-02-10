pixMultiplyByColor(PIX       *pixd,
                   PIX       *pixs,
                   BOX       *box,
                   l_uint32   color)
{
l_int32    i, j, bx, by, w, h, wpl;
l_int32    red, green, blue, rval, gval, bval, nrval, ngval, nbval;
l_float32  frval, fgval, fbval;
l_uint32  *data, *line;
PIX       *pixt;

    PROCNAME("pixMultiplyByColor");

    if (!pixs)
        return (PIX *)ERROR_PTR("pixs not defined", procName, pixd);
    if (pixGetDepth(pixs) != 32)
        return (PIX *)ERROR_PTR("pixs not 32 bpp", procName, pixd);
    if (pixd && (pixd != pixs))
        return (PIX *)ERROR_PTR("pixd neither null nor pixs", procName, pixd);

    if (!pixd)
        pixd = pixCopy(NULL, pixs);
    if (box) {
        boxGetGeometry(box, &bx, &by, NULL, NULL);
        pixt = pixClipRectangle(pixd, box, NULL);
    } else {
        pixt = pixClone(pixd);
    }


    extractRGBValues(color, &red, &green, &blue);
    frval = (1. / 255.) * red;
    fgval = (1. / 255.) * green;
    fbval = (1. / 255.) * blue;
    data = pixGetData(pixt);
    wpl = pixGetWpl(pixt);
    pixGetDimensions(pixt, &w, &h, NULL);
    for (i = 0; i < h; i++) {
        line = data + i * wpl;
        for (j = 0; j < w; j++) {
            extractRGBValues(line[j], &rval, &gval, &bval);
            nrval = (l_int32)(frval * rval + 0.5);
            ngval = (l_int32)(fgval * gval + 0.5);
            nbval = (l_int32)(fbval * bval + 0.5);
            composeRGBPixel(nrval, ngval, nbval, line + j);
        }
    }


    if (box)
        pixRasterop(pixd, bx, by, w, h, PIX_SRC, pixt, 0, 0);
    pixDestroy(&pixt);
    return pixd;
}
