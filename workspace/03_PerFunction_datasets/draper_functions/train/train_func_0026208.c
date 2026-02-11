RenderTransformedBoxa(PIX    *pixt,
                      BOXA   *boxa,
                      l_int32 i)
{
l_int32  j, n, rval, gval, bval;
BOX     *box;

    n = boxaGetCount(boxa);
    rval = (1413 * i) % 256;
    gval = (4917 * i) % 256;
    bval = (7341 * i) % 256;
    for (j = 0; j < n; j++) {
        box = boxaGetBox(boxa, j, L_CLONE);
        pixRenderHashBoxArb(pixt, box, 10, 3, i % 4, 1, rval, gval, bval);
        boxDestroy(&box);
    }
    return 0;
}
