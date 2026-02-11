PixTest1(PIX          *pixs,
         l_int32       size,
         l_float32     factor,
         L_REGPARAMS  *rp)
{
l_int32  w, h;
PIX     *pixm, *pixsd, *pixth, *pixd, *pixt;
PIXA    *pixa;

    pixm = pixsd = pixth = pixd = NULL;
    pixGetDimensions(pixs, &w, &h, NULL);


    startTimer();
    pixSauvolaBinarize(pixs, size, factor, 1, NULL, NULL, NULL, &pixd);
    fprintf(stderr, "\nSpeed: 1 tile,  %7.3f Mpix/sec\n",
            (w * h / 1000000.) / stopTimer());
    pixDestroy(&pixd);


    pixSauvolaBinarize(pixs, size, factor, 1, &pixm, &pixsd, &pixth, &pixd);
    pixa = pixaCreate(0);
    pixSaveTiled(pixm, pixa, 1, 1, 30, 8);
    pixSaveTiled(pixsd, pixa, 1, 0, 30, 8);
    pixSaveTiled(pixth, pixa, 1, 1, 30, 8);
    pixSaveTiled(pixd, pixa, 1, 0, 30, 8);
    pixt = pixaDisplay(pixa, 0, 0);
    regTestWritePixAndCheck(rp, pixt, IFF_JFIF_JPEG);
    if (rp->index < 5)
        pixDisplayWithTitle(pixt, 100, 100, NULL, rp->display);
    regTestWritePixAndCheck(rp, pixd, IFF_PNG);

    pixaDestroy(&pixa);
    pixDestroy(&pixm);
    pixDestroy(&pixsd);
    pixDestroy(&pixth);
    pixDestroy(&pixt);
    return pixd;
}
