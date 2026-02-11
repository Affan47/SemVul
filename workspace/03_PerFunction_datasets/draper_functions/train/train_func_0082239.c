main(int    argc,
         char **argv)
{
l_int32      w, h, d, n;
char        *filein1, *filein2, *fileout;
PIX         *pixs1, *pixs2;
static char  mainName[] = "bincompare";

    if (argc != 4)
        return ERROR_INT(" Syntax:  bincompare filein1 filein2 fileout",
                         mainName, 1);

    filein1 = argv[1];
    filein2 = argv[2];
    fileout = argv[3];
    if ((pixs1 = pixRead(filein1)) == NULL)
        return ERROR_INT("pixs1 not made", mainName, 1);
    if ((pixs2 = pixRead(filein2)) == NULL)
        return ERROR_INT("pixs2 not made", mainName, 1);

    pixGetDimensions(pixs1, &w, &h, &d);
    if (d != 1)
        return ERROR_INT("pixs1 not binary", mainName, 1);

    pixCountPixels(pixs1, &n, NULL);
    fprintf(stderr, "Number of fg pixels in file1 = %d\n", n);
    pixCountPixels(pixs2, &n, NULL);
    fprintf(stderr, "Number of fg pixels in file2 = %d\n", n);

#if XOR
    fprintf(stderr, "xor: 1 ^ 2\n");
    pixRasterop(pixs1, 0, 0, w, h, PIX_SRC ^ PIX_DST, pixs2, 0, 0);
    pixCountPixels(pixs1, &n, NULL);
    fprintf(stderr, "Number of fg pixels in XOR = %d\n", n);
    pixWrite(fileout, pixs1, IFF_PNG);
#elif  SUBTRACT_1_FROM_2
    fprintf(stderr, "subtract: 2 - 1\n");
    pixRasterop(pixs1, 0, 0, w, h, PIX_SRC & PIX_NOT(PIX_DST), pixs2, 0, 0);
    pixCountPixels(pixs1, &n, NULL);
    fprintf(stderr, "Number of fg pixels in 2 - 1 = %d\n", n);
    pixWrite(fileout, pixs1, IFF_PNG);
#elif  SUBTRACT_2_FROM_1
    fprintf(stderr, "subtract: 1 - 2\n");
    pixRasterop(pixs1, 0, 0, w, h, PIX_DST & PIX_NOT(PIX_SRC), pixs2, 0, 0);
    pixCountPixels(pixs1, &n, NULL);
    fprintf(stderr, "Number of fg pixels in 1 - 2 = %d\n", n);
    pixWrite(fileout, pixs1, IFF_PNG);
#else
    fprintf(stderr, "no comparison selected\n");
#endif

    return 0;
}
