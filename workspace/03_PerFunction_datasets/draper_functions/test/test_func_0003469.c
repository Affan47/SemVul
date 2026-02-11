main(int    argc,
     char **argv)
{
l_int32      max_dist, max_colors, sel_size, final_colors;
PIX         *pixs, *pixd, *pixt;
char        *filein, *fileout;
static char  mainName[] = "colorsegtest";

    if (argc != 3 && argc != 7)
	exit(ERROR_INT(
            "Syntax: colorsegtest filein fileout"
            " [max_dist max_colors sel_size final_colors]\n"
            " Default values are: max_dist = 120\n"
            "                     max_colors = 15\n"
            "                     sel_size = 4\n"
            "                     final_colors = 15\n", mainName, 1));

    filein = argv[1];
    fileout = argv[2];
    if (argc == 3) {
        max_dist = MAX_DIST;
        max_colors = MAX_COLORS;
        sel_size = SEL_SIZE;
        final_colors = FINAL_COLORS;
    }
    else {
        max_dist = atoi(argv[3]);
        max_colors = atoi(argv[4]);
        sel_size = atoi(argv[5]);
        final_colors = atoi(argv[6]);
    }

    if ((pixs = pixRead(filein)) == NULL)
	exit(ERROR_INT("pixs not made", mainName, 1));

    startTimer();
    pixt = pixRemoveColormap(pixs, REMOVE_CMAP_BASED_ON_SRC);
    pixd = pixColorSegment(pixt, max_dist, max_colors, sel_size, final_colors);
    fprintf(stderr, "Time to segment: %7.3f sec\n", stopTimer());
    pixWrite(fileout, pixd, IFF_PNG);

    pixDestroy(&pixs);
    pixDestroy(&pixd);
    return 0;
}
