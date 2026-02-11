pixUnsharpMaskingGrayFast(PIX       *pixs,
                          l_int32    halfwidth,
                          l_float32  fract,
                          l_int32    direction)
{
PIX  *pixd;

    PROCNAME("pixUnsharpMaskingGrayFast");

    if (!pixs)
        return (PIX *)ERROR_PTR("pixs not defined", procName, NULL);
    if (pixGetDepth(pixs) != 8 || pixGetColormap(pixs) != NULL)
        return (PIX *)ERROR_PTR("pixs not 8 bpp or has cmap", procName, NULL);
    if (fract <= 0.0 || halfwidth <= 0) {
        L_WARNING("no sharpening requested; clone returned", procName);
        return pixClone(pixs);
    }
    if (halfwidth != 1 && halfwidth != 2)
        return (PIX *)ERROR_PTR("halfwidth must be 1 or 2", procName, NULL);
    if (direction != L_HORIZ && direction != L_VERT &&
        direction != L_BOTH_DIRECTIONS)
        return (PIX *)ERROR_PTR("invalid direction", procName, NULL);

    if (direction != L_BOTH_DIRECTIONS)
        pixd = pixUnsharpMaskingGray1D(pixs, halfwidth, fract, direction);
    else
        pixd = pixUnsharpMaskingGray2D(pixs, halfwidth, fract);

    return pixd;
}
