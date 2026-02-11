pixBilinear(PIX        *pixs,
            l_float32  *vc,
            l_int32     incolor)
{
l_int32   d;
l_uint32  colorval;
PIX      *pixt1, *pixt2, *pixd;

    PROCNAME("pixBilinear");

    if (!pixs)
        return (PIX *)ERROR_PTR("pixs not defined", procName, NULL);
    if (!vc)
        return (PIX *)ERROR_PTR("vc not defined", procName, NULL);

    if (pixGetDepth(pixs) == 1)
        return pixBilinearSampled(pixs, vc, incolor);


    pixt1 = pixRemoveColormap(pixs, REMOVE_CMAP_BASED_ON_SRC);
    d = pixGetDepth(pixt1);
    if (d < 8)
        pixt2 = pixConvertTo8(pixt1, FALSE);
    else
        pixt2 = pixClone(pixt1);
    d = pixGetDepth(pixt2);


    colorval = 0;
    if (incolor == L_BRING_IN_WHITE) {
        if (d == 8)
            colorval = 255;
        else
            colorval = 0xffffff00;
    }

    if (d == 8)
        pixd = pixBilinearGray(pixt2, vc, colorval);
    else
        pixd = pixBilinearColor(pixt2, vc, colorval);
    pixDestroy(&pixt1);
    pixDestroy(&pixt2);
    return pixd;
}
