pixBlendBackgroundToColor(PIX       *pixd,
                          PIX       *pixs,
                          BOX       *box,
                          l_uint32   color,
                          l_float32  gamma,
                          l_int32    minval,
                          l_int32    maxval)
{
l_int32  x, y, w, h;
BOX     *boxt;
PIX     *pixt, *pixc, *pixr, *pixg;

    PROCNAME("pixBlendBackgroundToColor");

    if (!pixs)
        return (PIX *)ERROR_PTR("pixs not defined", procName, pixd);
    if (pixGetDepth(pixs) != 32)
        return (PIX *)ERROR_PTR("pixs not 32 bpp", procName, pixd);
    if (pixd && (pixd != pixs))
        return (PIX *)ERROR_PTR("pixd neither null nor pixs", procName, pixd);


    if (!pixd)
        pixd = pixCopy(NULL, pixs);
    if (box) {
        pixr = pixClipRectangle(pixd, box, &boxt);
        boxGetGeometry(boxt, &x, &y, &w, &h);
        pixc = pixCreate(w, h, 32);
        boxDestroy(&boxt);
    } else {
        pixc = pixCreateTemplate(pixs);
        pixr = pixClone(pixd);
    }
    pixSetAllArbitrary(pixc, color);


    pixg = pixConvertTo8(pixr, 0);
    pixGammaTRC(pixg, pixg, gamma, minval, maxval);
    pixSetRGBComponent(pixc, pixg, L_ALPHA_CHANNEL);


    pixt = pixBlendWithGrayMask(pixr, pixc, NULL, 0, 0);
    if (box) {
        pixRasterop(pixd, x, y, w, h, PIX_SRC, pixt, 0, 0);
        pixDestroy(&pixt);
    } else {
        pixTransferAllData(pixd, &pixt, 0, 0);
    }

    pixDestroy(&pixc);
    pixDestroy(&pixr);
    pixDestroy(&pixg);
    return pixd;
}
