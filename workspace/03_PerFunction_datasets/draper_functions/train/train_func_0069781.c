pixBlend(PIX       *pixs1,
         PIX       *pixs2,
         l_int32    x,
         l_int32    y,
         l_float32  fract)
{
l_int32    w1, h1, d1, d2;
BOX       *box;
PIX       *pixc, *pixt, *pixd;

    PROCNAME("pixBlend");

    if (!pixs1)
        return (PIX *)ERROR_PTR("pixs1 not defined", procName, NULL);
    if (!pixs2)
        return (PIX *)ERROR_PTR("pixs2 not defined", procName, NULL);


    d1 = pixGetDepth(pixs1);
    d2 = pixGetDepth(pixs2);
    if (d1 == 1 && d2 > 1)
        return (PIX *)ERROR_PTR("mixing gray or color with 1 bpp",
                                procName, NULL);


    pixt = pixRemoveColormap(pixs2, REMOVE_CMAP_BASED_ON_SRC);
    d2 = pixGetDepth(pixt);


    w1 = pixGetWidth(pixs1);
    h1 = pixGetHeight(pixs1);
    box = boxCreate(-x, -y, w1, h1);
    pixc = pixClipRectangle(pixt, box, NULL);
    boxDestroy(&box);
    if (!pixc) {
        L_WARNING("box doesn't overlap pix", procName);
        return NULL;
    }
    x = L_MAX(0, x);
    y = L_MAX(0, y);

    if (d2 == 1)
        pixd = pixBlendMask(NULL, pixs1, pixc, x, y, fract,
                            L_BLEND_WITH_INVERSE);
    else if (d2 == 8)
        pixd = pixBlendGray(NULL, pixs1, pixc, x, y, fract,
                            L_BLEND_GRAY, 0, 0);
    else
        pixd = pixBlendColor(NULL, pixs1, pixc, x, y, fract, 0, 0);

    pixDestroy(&pixc);
    pixDestroy(&pixt);
    return pixd;
}
