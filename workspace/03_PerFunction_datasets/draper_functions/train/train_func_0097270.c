AddTextAndSave(PIXA        *pixa,
               PIX         *pixs,
               l_int32      newrow,
               L_BMF       *bmf,
               const char  *textstr,
               l_int32      location,
               l_uint32     val)
{
l_int32  n, ovf;
PIX     *pixt;

    pixt = pixAddSingleTextblock(pixs, bmf, textstr, val, location, &ovf);
    n = pixaGetCount(pixa);
    pixSaveTiledOutline(pixt, pixa, 1, newrow, 30, 2, 32);
    if (ovf) fprintf(stderr, "Overflow writing text in image %d\n", n + 1);
    pixDestroy(&pixt);
    return;
}
