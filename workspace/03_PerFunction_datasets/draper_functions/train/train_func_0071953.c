pixUnsharpMaskingGray(PIX       *pixs,
                      l_int32    smooth,
                      l_float32  fract)
{
l_int32  w, h, d;
PIX     *pixc, *pixd;
PIXACC  *pixacc;

    PROCNAME("pixUnsharpMaskingGray");

    if (!pixs)
        return (PIX *)ERROR_PTR("pixs not defined", procName, NULL);
    pixGetDimensions(pixs, &w, &h, &d);
    if (d != 8)
        return (PIX *)ERROR_PTR("pixs not 8 bpp", procName, NULL);

    if (fract <= 0.0) {
        L_WARNING("no fraction added back in", procName);
        return pixClone(pixs);
    }

    if ((pixc = pixBlockconvGray(pixs, NULL, smooth, smooth)) == NULL)
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
