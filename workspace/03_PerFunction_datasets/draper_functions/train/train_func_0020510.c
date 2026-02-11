main(int    argc,
         char **argv)
{
char        *filein, *fileout;
l_int32      i, j, w, d, nhue, nsat, tilewidth;
l_float32    scale, dhue, dsat, delhue, delsat;
PIX         *pixs, *pixt1, *pixt2, *pixd;
PIXA        *pixa;
static char  mainName[] = "modifyhuesat";

    if (argc != 7)
        return ERROR_INT(
            " Syntax: modifyhuesat filein nhue dhue nsat dsat fileout",
            mainName, 1);

    filein = argv[1];
    nhue = atoi(argv[2]);
    dhue = atof(argv[3]);
    nsat = atoi(argv[4]);
    dsat = atof(argv[5]);
    fileout = argv[6];

    if (nhue % 2 == 0) {
        nhue++;
        fprintf(stderr, "nhue must be odd; raised to %d\n", nhue);
    }
    if (nsat % 2 == 0) {
        nsat++;
        fprintf(stderr, "nsat must be odd; raised to %d\n", nsat);
    }

    if ((pixt1 = pixRead(filein)) == NULL)
        return ERROR_INT("pixt1 not read", mainName, 1);
    pixGetDimensions(pixt1, &w, NULL, NULL);
    scale = 250.0 / (l_float32)w;
    pixt2 = pixScale(pixt1, scale, scale);
    pixs = pixConvertTo32(pixt2);
    pixDestroy(&pixt1);
    pixDestroy(&pixt2);

    pixGetDimensions(pixs, &w, NULL, &d);
    pixa = pixaCreate(nhue * nsat);
    for (i = 0; i < nsat; i++) {
        delsat = (i - nsat / 2) * dsat;
	pixt1 = pixModifySaturation(NULL, pixs, delsat);
        for (j = 0; j < nhue; j++) {
            delhue = (j - nhue / 2) * dhue;
            pixt2 = pixModifyHue(NULL, pixt1, delhue);
            pixaAddPix(pixa, pixt2, L_INSERT);
        }
        pixDestroy(&pixt1);
    }

    tilewidth = L_MIN(w, 1500 / nsat);
    pixd = pixaDisplayTiledAndScaled(pixa, d, tilewidth, nsat, 0, 25, 3);
    pixWrite(fileout, pixd, IFF_JFIF_JPEG);

    pixDestroy(&pixs);
    pixDestroy(&pixd);
    pixaDestroy(&pixa);
    return 0;
}
