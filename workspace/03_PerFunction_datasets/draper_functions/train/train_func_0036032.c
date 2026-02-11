pixAddBorderGeneral(PIX      *pixs,
                    l_int32   left,
                    l_int32   right,
                    l_int32   top,
                    l_int32   bot,
                    l_uint32  val)
{
l_int32  ws, hs, wd, hd, d, maxval, op;
PIX     *pixd;

    PROCNAME("pixAddBorderGeneral");

    if (!pixs)
        return (PIX *)ERROR_PTR("pixs not defined", procName, NULL);
    if (left < 0 || right < 0 || top < 0 || bot < 0)
        return (PIX *)ERROR_PTR("negative border added!", procName, NULL);

    pixGetDimensions(pixs, &ws, &hs, &d);
    wd = ws + left + right;
    hd = hs + top + bot;
    if ((pixd = pixCreateNoInit(wd, hd, d)) == NULL)
        return (PIX *)ERROR_PTR("pixd not made", procName, NULL);
    pixCopyResolution(pixd, pixs);
    pixCopyColormap(pixd, pixs);


    maxval = (d == 32) ? 0xffffff00 : (1 << d) - 1;
    op = UNDEF;
    if (val == 0)
        op = PIX_CLR;
    else if (val >= maxval)
        op = PIX_SET;
    if (op == UNDEF) {
        pixSetAllArbitrary(pixd, val);
    } else {
        pixRasterop(pixd, 0, 0, left, hd, op, NULL, 0, 0);
        pixRasterop(pixd, wd - right, 0, right, hd, op, NULL, 0, 0);
        pixRasterop(pixd, 0, 0, wd, top, op, NULL, 0, 0);
        pixRasterop(pixd, 0, hd - bot, wd, bot, op, NULL, 0, 0);
    }


    pixRasterop(pixd, left, top, ws, hs, PIX_SRC, pixs, 0, 0);
    return pixd;
}
