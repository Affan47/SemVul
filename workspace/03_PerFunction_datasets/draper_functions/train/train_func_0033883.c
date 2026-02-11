pixQuantizeIfFewColors(PIX     *pixs,
                       l_int32  maxcolors,
                       l_int32  mingraycolors,
                       l_int32  octlevel,
                       PIX    **ppixd)
{
l_int32  d, ncolors, iscolor, graycolors;
PIX     *pixg, *pixd;

    PROCNAME("pixQuantizeIfFewColors");

    if (!ppixd)
        return ERROR_INT("&pixd not defined", procName, 1);
    *ppixd = NULL;
    if (!pixs)
        return ERROR_INT("pixs not defined", procName, 1);
    d = pixGetDepth(pixs);
    if (d != 8 && d != 32)
        return ERROR_INT("pixs not defined", procName, 1);
    if (pixGetColormap(pixs) != NULL) {
        *ppixd = pixClone(pixs);
        return 0;
    }
    if (maxcolors <= 0)
        maxcolors = 15;
    if (maxcolors > 50)
        L_WARNING("maxcolors > 50; very large!", procName);
    if (mingraycolors <= 0)
        mingraycolors = 10;
    if (mingraycolors > 30)
        L_WARNING("mingraycolors > 30; very large!", procName);
    if (octlevel != 3 && octlevel != 4) {
        L_WARNING("invalid octlevel; setting to 3", procName);
        octlevel = 3;
    }


    pixColorsForQuantization(pixs, 0, &ncolors, &iscolor, 0);
    if (ncolors > maxcolors)
        return ERROR_INT("too many colors", procName, 1);


    if (iscolor) {
        pixd = pixFewColorsOctcubeQuant1(pixs, octlevel);
        if (!pixd) {
            pixd = pixFewColorsOctcubeQuant1(pixs, octlevel - 1);
            if (octlevel == 3)
                L_WARNING("quantized at level 2; low quality", procName);
        }
    }
    else  {
        if (d == 32)
            pixg = pixConvertRGBToLuminance(pixs);
        else
            pixg = pixClone(pixs);
        graycolors = L_MAX(mingraycolors, (l_int32)(1.5 * ncolors));
        graycolors = L_MIN(graycolors, 256);
        if (graycolors < 16)
            pixd = pixThresholdTo4bpp(pixg, graycolors, 1);
        else
            pixd = pixThresholdOn8bpp(pixg, graycolors, 1);
        pixDestroy(&pixg);
    }
    *ppixd = pixd;

    if (!pixd)
        return ERROR_INT("pixd not made", procName, 1);
    else
        return 0;
}
