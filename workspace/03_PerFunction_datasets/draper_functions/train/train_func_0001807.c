main(int    argc,
         char **argv)
{
PIX          *pix;
PIXA         *pixa;
L_REGPARAMS  *rp;

    if (regTestSetup(argc, argv, &rp))
        return 1;

    pixa = TestHardlight("hardlight1_1.jpg", "hardlight1_2.jpg", rp);
    pix = pixaDisplay(pixa, 0, 0);
    regTestWritePixAndCheck(rp, pix, IFF_PNG);
    pixDisplayWithTitle(pix, 0, 0, NULL, rp->display);
    pixaDestroy(&pixa);
    pixDestroy(&pix);

    pixa = TestHardlight("hardlight2_1.jpg", "hardlight2_2.jpg", rp);
    pix = pixaDisplay(pixa, 0, 500);
    regTestWritePixAndCheck(rp, pix, IFF_PNG);
    pixDisplayWithTitle(pix, 0, 0, NULL, rp->display);
    pixaDestroy(&pixa);
    pixDestroy(&pix);

    return regTestCleanup(rp);
}
