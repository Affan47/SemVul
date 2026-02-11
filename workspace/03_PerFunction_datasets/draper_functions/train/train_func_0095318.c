pixUnsharpMaskingGray(PIX       *pixs,
                      l_int32    halfwidth,
                      l_float32  fract)
{
l_int32  w, h, d;
PIX     *pixc, *pixd;
PIXACC  *pixacc;

    PROCNAME("pixUnsharpMaskingGray");

    if (!pixs)
        return (PIX *)ERROR_PTR("pixs not defined", procName, NULL);
    pixGetDimensions(pixs, &w, &h, &d);
    if (d != 8 || pixGetColormap(pixs) != NULL)
        return (PIX *)ERROR_PTR("pixs not 8 bpp or has cmap", procName, NULL);
    if (fract <= 0.0 || halfwidth <= 0) {
        L_WARNING("no sharpening requested; clone returned\n", procName);
        return pixClone(pixs);
    }
    if (halfwidth == 1 || halfwidth == 2)
        return pixUnsharpMaskingGrayFast(pixs, halfwidth, fract,
                                         L_BOTH_DIRECTIONS);

    if ((pixc = pixBlockconvGray(pixs, NULL, halfwidth, halfwidth)) == NULL)
        return (PIX *)ERROR_PTR("pixc not made", procName, NULL);


    pixacc = pixaccCreate(w, h, 1);
    pixaccAdd(pixacc, pixs);
    pixaccSubtract(pixacc, pixc);
    pixaccMultConst(pixacc, fract);
    pixaccAdd(pixacc, pixs);
    pixd = pixaccFinal(pixacc, 8);
    pixaccDestroy(&pixacc);

    pixDestroy(&pixc);
    return pixd;
}
