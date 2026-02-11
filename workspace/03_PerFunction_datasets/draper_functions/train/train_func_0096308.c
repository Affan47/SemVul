pixSetAllArbitrary(PIX      *pix,
                   l_uint32  val)
{
l_int32    i, j, w, h, d, wpl, npix;
l_uint32   maxval, wordval;
l_uint32  *data, *line;

    PROCNAME("pixSetAllArbitrary");

    if (!pix)
        return ERROR_INT("pix not defined", procName, 1);

    pixGetDimensions(pix, &w, &h, &d);
    if (d == 32)
        maxval = 0xffffffff;
    else
        maxval = (1 << d) - 1;
    if (val < 0) {
        L_WARNING("invalid pixel value; set to 0", procName);
        val = 0;
    }
    if (val > maxval) {
        L_WARNING_INT("invalid pixel val; set to maxval = %d",
                      procName, maxval);
        val = maxval;
    }


    wordval = 0;
    npix = 32 / d;
    for (j = 0; j < npix; j++)
        wordval |= (val << (j * d));

    wpl = pixGetWpl(pix);
    data = pixGetData(pix);
    for (i = 0; i < h; i++) {
        line = data + i * wpl;
        for (j = 0; j < wpl; j++) {
            *(line + j) = wordval;
        }
    }

    return 0;
}
