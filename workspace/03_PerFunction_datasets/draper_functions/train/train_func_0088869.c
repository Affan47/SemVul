pixRotate(PIX       *pixs,
          l_float32  angle,
          l_int32    type,
          l_int32    incolor,
          l_int32    width,
          l_int32    height)
{
l_int32    d;
l_uint32   fillval;
PIX       *pixt1, *pixt2, *pixt3, *pixd;
PIXCMAP   *cmap;

    PROCNAME("pixRotate");

    if (!pixs)
        return (PIX *)ERROR_PTR("pixs not defined", procName, NULL);
    if (type != L_ROTATE_SHEAR && type != L_ROTATE_AREA_MAP)
        return (PIX *)ERROR_PTR("invalid type", procName, NULL);
    if (incolor != L_BRING_IN_WHITE && incolor != L_BRING_IN_BLACK)
        return (PIX *)ERROR_PTR("invalid incolor", procName, NULL);

    if (L_ABS(angle) < VERY_SMALL_ANGLE)
        return pixClone(pixs);


    if ((cmap = pixGetColormap(pixs)) != NULL)
        pixt1 = pixRemoveColormap(pixs, REMOVE_CMAP_BASED_ON_SRC);
    else
        pixt1 = pixClone(pixs);


    pixt2 = pixEmbedForRotation(pixt1, angle, incolor, width, height);


    d = pixGetDepth(pixt2);
    if (type == L_ROTATE_AREA_MAP && d > 1 && d < 8)
        pixt3 = pixConvertTo8(pixt2, FALSE);
    else
        pixt3 = pixClone(pixt2);


    d = pixGetDepth(pixt3);
    if (d == 1 || type == L_ROTATE_SHEAR)
        pixd = pixRotateShearCenter(pixt3, angle, incolor);
    else {
        fillval = 0;
        if (incolor == L_BRING_IN_WHITE) {
            if (d == 8)
                fillval = 255;
            else
                fillval = 0xffffff00;
        }
        if (d == 8)
            pixd = pixRotateAMGray(pixt3, angle, fillval);
        else
            pixd = pixRotateAMColor(pixt3, angle, fillval);
    }

    pixDestroy(&pixt1);
    pixDestroy(&pixt2);
    pixDestroy(&pixt3);
    return pixd;
}
