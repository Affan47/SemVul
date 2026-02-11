pixSetBlackOrWhiteBoxa(PIX     *pixs,
                       BOXA    *boxa,
                       l_int32  op)
{
l_int32   i, n, d, index;
l_uint32  color;
BOX      *box;
PIX      *pixd;
PIXCMAP  *cmap;

    PROCNAME("pixSetBlackOrWhiteBoxa");

    if (!pixs)
        return (PIX *)ERROR_PTR("pixs not defined", procName, NULL);
    if (!boxa)
        return pixCopy(NULL, pixs);
    if ((n = boxaGetCount(boxa)) == 0)
        return pixCopy(NULL, pixs);

    pixd = pixCopy(NULL, pixs);
    d = pixGetDepth(pixd);
    if (d == 1) {
        for (i = 0; i < n; i++) {
            box = boxaGetBox(boxa, i, L_CLONE);
            if (op == L_SET_WHITE)
                pixClearInRect(pixd, box);
            else
                pixSetInRect(pixd, box);
            boxDestroy(&box);
        }
        return pixd;
    }

    cmap = pixGetColormap(pixs);
    if (cmap) {
        color = (op == L_SET_WHITE) ? 1 : 0;
        pixcmapAddBlackOrWhite(cmap, color, &index);
    } else if (d == 8) {
        color = (op == L_SET_WHITE) ? 0xff : 0x0;
    } else if (d == 32) {
        color = (op == L_SET_WHITE) ? 0xffffff00 : 0x0;
    } else if (d == 2) {
        color = (op == L_SET_WHITE) ? 0x3 : 0x0;
    } else if (d == 4) {
        color = (op == L_SET_WHITE) ? 0xf : 0x0;
    } else if (d == 16) {
        color = (op == L_SET_WHITE) ? 0xffff : 0x0;
    } else {
        pixDestroy(&pixd);
        return (PIX *)ERROR_PTR("invalid depth", procName, NULL);
    }

    for (i = 0; i < n; i++) {
        box = boxaGetBox(boxa, i, L_CLONE);
        if (cmap)
            pixSetInRectArbitrary(pixd, box, index);
        else
            pixSetInRectArbitrary(pixd, box, color);
        boxDestroy(&box);
    }

    return pixd;
}
