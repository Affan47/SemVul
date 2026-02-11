pixTilingPaintTile(PIX        *pixd,
                   l_int32     i,
                   l_int32     j,
                   PIX        *pixs,
                   PIXTILING  *pt)
{
l_int32  width, height;

    PROCNAME("pixTilingPaintTile");

    if (!pixd)
        return ERROR_INT("pixd not defined", procName, 1);
    if (!pixs)
        return ERROR_INT("pixs not defined", procName, 1);
    if (!pt)
        return ERROR_INT("pt not defined", procName, 1);
    if (i < 0 || i >= pt->ny)
        return ERROR_INT("invalid row index i", procName, 1);
    if (j < 0 || j >= pt->nx)
        return ERROR_INT("invalid column index j", procName, 1);

    width = pixGetWidth(pixs) - 2 * pt->xoverlap;
    height = pixGetHeight(pixs) - 2 * pt->yoverlap;
    pixRasterop(pixd, j * pt->w, i * pt->h, width, height, PIX_SRC,
                pixs, pt->xoverlap, pt->yoverlap);
    return 0;
}
