pixAverageInRect(PIX        *pix,
                 BOX        *box,
                 l_float32  *pave)
{
l_int32    w, h, d, wpl, i, j, xstart, xend, ystart, yend, bw, bh;
l_uint32  *data, *line;
l_float64  ave;

    PROCNAME("pixAverageInRect");

    if (!pave)
        return ERROR_INT("pave not defined", procName, 1);
    *pave = 0;
    if (!pix)
        return ERROR_INT("pix not defined", procName, 1);
    pixGetDimensions(pix, &w, &h, &d);
    if (d != 1 && d != 2 && d != 4 && d != 8)
        return ERROR_INT("pix not 1, 2, 4 or 8 bpp", procName, 1);
    if (pixGetColormap(pix) != NULL)
        return ERROR_INT("pix is colormapped", procName, 1);

    if (boxClipToRectangleParams(box, w, h, &xstart, &ystart, &xend, &yend,
                                 &bw, &bh) == 1)
        return ERROR_INT("invalid clipping box", procName, 1);

    wpl = pixGetWpl(pix);
    data = pixGetData(pix);
    ave = 0;
    for (i = ystart; i < yend; i++) {
        line = data + i * wpl;
        for (j = xstart; j < xend; j++) {
            if (d == 1)
                ave += GET_DATA_BIT(line, j);
            else if (d == 2)
                ave += GET_DATA_DIBIT(line, j);
            else if (d == 4)
                ave += GET_DATA_QBIT(line, j);
            else
                ave += GET_DATA_BYTE(line, j);
        }
    }

    *pave = ave / (bw * bh);
    return 0;
}
