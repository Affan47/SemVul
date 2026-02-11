freadHeaderPnm(FILE     *fp,
               PIX     **ppix,
               l_int32  *pwidth,
               l_int32  *pheight,
               l_int32  *pdepth,
               l_int32  *ptype,
               l_int32  *pbps,
               l_int32  *pspp)
{
l_int32  w, h, d, type;
l_int32  maxval;

    PROCNAME("freadHeaderPnm");

    if (!fp)
        return ERROR_INT("fp not defined", procName, 1);
    if (!pwidth || !pheight || !pdepth || !ptype)
        return ERROR_INT("input ptr(s) not defined", procName, 1);

    if (fscanf(fp, "P%d\n", &type) != 1)
        return ERROR_INT("invalid read for type", procName, 1);
    if (type < 1 || type > 6)
        return ERROR_INT("invalid pnm file", procName, 1);

    if (pnmSkipCommentLines(fp))
        return ERROR_INT("no data in file", procName, 1);

    if (fscanf(fp, "%d %d\n", &w, &h) != 2)
        return ERROR_INT("invalid read for w,h", procName, 1);
    if (w <= 0 || h <= 0 || w > MAX_PNM_WIDTH || h > MAX_PNM_HEIGHT)
        return ERROR_INT("invalid sizes", procName, 1);


    if (type == 1 || type == 4)
        d = 1;
    else if (type == 2 || type == 5) {
        if (fscanf(fp, "%d\n", &maxval) != 1)
            return ERROR_INT("invalid read for maxval (2,5)", procName, 1);
        if (maxval == 3)
            d = 2;
        else if (maxval == 15)
            d = 4;
        else if (maxval == 255)
            d = 8;
        else if (maxval == 0xffff)
            d = 16;
        else {
            fprintf(stderr, "maxval = %d\n", maxval);
            return ERROR_INT("invalid maxval", procName, 1);
        }
    }
    else {
        if (fscanf(fp, "%d\n", &maxval) != 1)
            return ERROR_INT("invalid read for maxval (3,6)", procName, 1);
        if (maxval != 255)
            L_WARNING_INT("unexpected maxval = %d", procName, maxval);
        d = 32;
    }
    *pwidth = w;
    *pheight = h;
    *pdepth = d;
    *ptype = type;
    if (pbps) *pbps = (d == 32) ? 8 : d;
    if (pspp) *pspp = (d == 32) ? 3 : 1;

    if (!ppix)
        return 0;

    if ((*ppix = pixCreate(w, h, d)) == NULL)
        return ERROR_INT( "pix not made", procName, 1);
    return 0;
}
