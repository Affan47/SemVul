main(int    argc,
     char **argv)
{
char        *infile, *outfile;
l_int32      d;
PIX         *pixs, *pixgr, *pixb;
static char  mainName[] = "showedges";

    if (argc != 3)
	exit(ERROR_INT(" Syntax: showedges infile outfile", mainName, 1));

    infile = argv[1];
    outfile = argv[2];

    pixs = pixRead(infile);
    d = pixGetDepth(pixs);
    if (d != 8 && d != 32)
	exit(ERROR_INT("d not 8 or 32 bpp", mainName, 1));

    pixgr = pixHalfEdgeByBandpass(pixs, SMOOTH_WIDTH_1, SMOOTH_WIDTH_1,
                                        SMOOTH_WIDTH_2, SMOOTH_WIDTH_2);
    pixb = pixThresholdToBinary(pixgr, THRESHOLD);
    pixInvert(pixb, pixb);

    pixWrite(outfile, pixb, IFF_PNG);

    return 0;
}
