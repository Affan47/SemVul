pixSetTextblock(PIX         *pixs,
                BMF         *bmf,
                const char  *textstr,
                l_uint32     val,
                l_int32      x0,
                l_int32      y0,
                l_int32      wtext,
                l_int32      firstindent,
                l_int32     *poverflow)
{
char     *linestr;
l_int32   d, h, i, w, x, y, nlines, htext, xwidth, wline, ovf, overflow;
SARRAY   *salines;
PIXCMAP  *cmap;

    PROCNAME("pixSetTextblock");

    if (!pixs)
        return ERROR_INT("pixs not defined", procName, 1);
    if (!bmf)
        return ERROR_INT("bmf not defined", procName, 1);
    if (!textstr)
        return ERROR_INT("textstr not defined", procName, 1);
    if (val < 0)
        return ERROR_INT("val must be >= 0", procName, 1);

    pixGetDimensions(pixs, &w, &h, &d);
    cmap = pixGetColormap(pixs);
    if (d == 2 && val > 0x03 && !cmap)
        return ERROR_INT("for 2 bpp, val must be < 4", procName, 1);
    if (d == 4 && val > 0x0f && !cmap)
        return ERROR_INT("for 4 bpp, val must be < 16", procName, 1);
    if (d == 8 && val > 0xff && !cmap)
        return ERROR_INT("for 8 bpp, val must be < 256", procName, 1);
    if (d == 16 && val > 0xffff)
        return ERROR_INT("for 16 bpp, val must be <= 0xffff", procName, 1);
    if (d == 32 && val < 256)
        return ERROR_INT("for RGB, val must be >= 256", procName, 1);

    if (w < x0 + wtext) {
        L_WARNING("reducing width of textblock", procName);
        wtext = w - x0 - w / 10;
        if (wtext <= 0)
            return ERROR_INT("wtext too small; no room for text", procName, 1);
    }

    salines = bmfGetLineStrings(bmf, textstr, wtext, firstindent, &htext);
    if (!salines)
        return ERROR_INT("line string sa not made", procName, 1);
    nlines = sarrayGetCount(salines);
    bmfGetWidth(bmf, 'x', &xwidth);

    y = y0;
    overflow = 0;
    for (i = 0; i < nlines; i++) {
        if (i == 0)
            x = x0 + firstindent * xwidth;
        else
            x = x0;
        linestr = sarrayGetString(salines, i, 0);
        pixSetTextline(pixs, bmf, linestr, val, x, y, &wline, &ovf);
        y += bmf->lineheight + bmf->vertlinesep;
        if (ovf)
            overflow = 1;
    }


    if (h < y0 - bmf->baselinetab[93] + htext)
        overflow = 1;
    if (poverflow)
        *poverflow = overflow;

    sarrayDestroy(&salines);
    return 0;
}
