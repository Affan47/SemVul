bmfGetStringWidth(L_BMF       *bmf,
                  const char  *textstr,
                  l_int32     *pw)
{
char     chr;
l_int32  i, w, width, nchar;

    PROCNAME("bmfGetStringWidth");

    if (!bmf)
        return ERROR_INT("bmf not defined", procName, 1);
    if (!textstr)
        return ERROR_INT("teststr not defined", procName, 1);
    if (!pw)
        return ERROR_INT("&w not defined", procName, 1);

    nchar = strlen(textstr);
    w = 0;
    for (i = 0; i < nchar; i++) {
        chr = textstr[i];
        bmfGetWidth(bmf, chr, &width);
        if (width != UNDEF)
            w += width + bmf->kernwidth;
    }
    w -= bmf->kernwidth;

    *pw = w;
    return 0;
}
