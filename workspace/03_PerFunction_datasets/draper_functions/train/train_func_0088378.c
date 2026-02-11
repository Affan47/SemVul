pixSetUnderTransparency(PIX      *pixs,
                        l_uint32  val,
                        l_int32   debugflag)
{
l_int32   isblack, rval, gval, bval;
PIX      *pixr, *pixg, *pixb, *pixalpha, *pixm, *pixt, *pixd;
PIXA     *pixa;

    PROCNAME("pixSetUnderTransparency");

    if (!pixs || pixGetDepth(pixs) != 32)
        return (PIX *)ERROR_PTR("pixs not defined or not 32 bpp",
                                procName, NULL);

    pixalpha = pixGetRGBComponent(pixs, L_ALPHA_CHANNEL);
    pixZero(pixalpha, &isblack);
    if (isblack) {
        L_WARNING(
            "alpha channel is fully transparent; likely invalid; ignoring",
            procName);
        pixDestroy(&pixalpha);
        return pixCopy(NULL, pixs);
    }
    pixr = pixGetRGBComponent(pixs, COLOR_RED);
    pixg = pixGetRGBComponent(pixs, COLOR_GREEN);
    pixb = pixGetRGBComponent(pixs, COLOR_BLUE);


    pixm = pixThresholdToBinary(pixalpha, 1);

    if (debugflag) {
        pixa = pixaCreate(0);
        pixSaveTiled(pixs, pixa, 1, 1, 20, 32);
        pixSaveTiled(pixm, pixa, 1, 0, 20, 0);
        pixSaveTiled(pixr, pixa, 1, 1, 20, 0);
        pixSaveTiled(pixg, pixa, 1, 0, 20, 0);
        pixSaveTiled(pixb, pixa, 1, 0, 20, 0);
        pixSaveTiled(pixalpha, pixa, 1, 0, 20, 0);
    }


    extractRGBValues(val, &rval, &gval, &bval);
    pixSetMasked(pixr, pixm, rval);
    pixSetMasked(pixg, pixm, gval);
    pixSetMasked(pixb, pixm, bval);
    pixd = pixCreateRGBImage(pixr, pixg, pixb);
    pixSetRGBComponent(pixd, pixalpha, L_ALPHA_CHANNEL);

    if (debugflag) {
        pixSaveTiled(pixr, pixa, 1, 1, 20, 0);
        pixSaveTiled(pixg, pixa, 1, 0, 20, 0);
        pixSaveTiled(pixb, pixa, 1, 0, 20, 0);
        pixSaveTiled(pixd, pixa, 1, 1, 20, 0);
        pixt = pixaDisplay(pixa, 0, 0);
        pixWriteTempfile("/tmp", "rgb.png", pixt, IFF_PNG, NULL);
        pixDestroy(&pixt);
        pixaDestroy(&pixa);
    }

    pixDestroy(&pixr);
    pixDestroy(&pixg);
    pixDestroy(&pixb);
    pixDestroy(&pixm);
    pixDestroy(&pixalpha);
    return pixd;
}
