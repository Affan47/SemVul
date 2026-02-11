makeMosaicStrips(l_int32  w,
                 l_int32  h,
                 l_int32  direction,
                 l_int32  size)
{
l_int32  i, nstrips, extra;
BOX     *box;
BOXA    *boxa;

    PROCNAME("makeMosaicStrips");

    if (w < 1 || h < 1)
        return (BOXA *)ERROR_PTR("invalid w or h", procName, NULL);
    if (direction != L_SCAN_HORIZONTAL && direction != L_SCAN_VERTICAL)
        return (BOXA *)ERROR_PTR("invalid direction", procName, NULL);
    if (size < 1)
        return (BOXA *)ERROR_PTR("size < 1", procName, NULL);

    boxa = boxaCreate(0);
    if (direction == L_SCAN_HORIZONTAL) {
        nstrips = w / size;
        for (i = 0; i < nstrips; i++) {
            box = boxCreate(i * size, 0, size, h);
            boxaAddBox(boxa, box, L_INSERT);
        }
        if ((extra = w % size) > 0) {
            box = boxCreate(nstrips * size, 0, extra, h);
            boxaAddBox(boxa, box, L_INSERT);
        }
    } else {
        nstrips = h / size;
        for (i = 0; i < nstrips; i++) {
            box = boxCreate(0, i * size, w, size);
            boxaAddBox(boxa, box, L_INSERT);
        }
        if ((extra = h % size) > 0) {
            box = boxCreate(0, nstrips * size, w, extra);
            boxaAddBox(boxa, box, L_INSERT);
        }
    }
    return boxa;
}
