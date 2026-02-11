main(int    argc,
     char **argv)
{
l_int32       count, display, success;
FILE         *fp;
PIX          *pixs, *pixd;
L_REGPARAMS  *rp;

    if (regTestSetup(argc, argv, &fp, &display, &success, &rp))
              return 1;

    count = 0;
    fprintf(stderr, "Test binary image:\n");
    pixs = pixRead(BINARY_IMAGE);
    RotateTest(pixs, 1, &count, rp);
    pixDestroy(&pixs);

    fprintf(stderr, "Test 2 bpp cmapped image with filled cmap:\n");
    pixs = pixRead(TWO_BPP_IMAGE);
    RotateTest(pixs, 1, &count, rp);
    pixDestroy(&pixs);

    fprintf(stderr, "Test 4 bpp cmapped image with unfilled cmap:\n");
    pixs = pixRead(FOUR_BPP_IMAGE1);
    RotateTest(pixs, 1, &count, rp);
    pixDestroy(&pixs);

    fprintf(stderr, "Test 4 bpp cmapped image with filled cmap:\n");
    pixs = pixRead(FOUR_BPP_IMAGE2);
    RotateTest(pixs, 1, &count, rp);
    pixDestroy(&pixs);

    fprintf(stderr, "Test 8 bpp grayscale image:\n");
    pixs = pixRead(EIGHT_BPP_IMAGE);
    RotateTest(pixs, 1, &count, rp);
    pixDestroy(&pixs);

    fprintf(stderr, "Test 8 bpp grayscale cmap image:\n");
    pixs = pixRead(EIGHT_BPP_CMAP_IMAGE1);
    RotateTest(pixs, 1, &count, rp);
    pixDestroy(&pixs);

    fprintf(stderr, "Test 8 bpp color cmap image:\n");
    pixs = pixRead(EIGHT_BPP_CMAP_IMAGE2);
    pixd = pixOctreeColorQuant(pixs, 200, 0);
    RotateTest(pixd, 2, &count, rp);
    pixDestroy(&pixs);
    pixDestroy(&pixd);

    fprintf(stderr, "Test rgb image:\n");
    pixs = pixRead(RGB_IMAGE);
    RotateTest(pixs, 4, &count, rp);
    pixDestroy(&pixs);

    regTestCleanup(argc, argv, fp, success, rp);
    return 0;
}
