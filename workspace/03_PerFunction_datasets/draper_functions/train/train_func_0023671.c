main(int    argc,
     char **argv)
{
char        *filein;
l_int32      i, n, ns;
BOX         *box;
BOXA        *boxa, *boxas;
PIX         *pixs, *pixt;
PIXA        *pixa, *pixas, *pixas2;
static char  mainName[] = "sorttest";

    if (argc != 2)
	exit(ERROR_INT(" Syntax:  sorttest filein", mainName, 1));

    filein = argv[1];

    if ((pixs = pixRead(filein)) == NULL)
	exit(ERROR_INT("pixs not made", mainName, 1));

#if 0
    boxa = pixConnComp(pixs, NULL, 8);
    n = boxaGetCount(boxa);

    boxas = boxaSort(boxa, L_SORT_BY_PERIMETER, L_SORT_DECREASING, NULL);
    ns = boxaGetCount(boxas);
    fprintf(stderr, "Number of cc: n = %d, ns = %d\n", n, ns);
    boxaWrite("/tmp/junkboxa.ba", boxas);

    for (i = 0; i < n; i++) {
	box = boxaGetBox(boxas, i, L_CLONE);
	pixRenderBox(pixs, box, 2, L_FLIP_PIXELS);
	boxDestroy(&box);
    }
    pixWrite("/tmp/junkout.png", pixs, IFF_PNG);
    boxaDestroy(&boxa);
    boxaDestroy(&boxas);
#endif


#if 1
    boxa = pixConnComp(pixs, &pixa, 8);
    n = pixaGetCount(pixa);

    pixas = pixaSort(pixa, L_SORT_BY_Y, L_SORT_INCREASING, NULL, L_CLONE);
    ns = pixaGetCount(pixas);
    fprintf(stderr, "Number of cc: n = %d, ns = %d\n", n, ns);
    pixaWrite("/tmp/junkpixa.pa", pixas);
    pixas2 = pixaRead("/tmp/junkpixa.pa");
    pixaWrite("/tmp/junkpixa2.pa", pixas2);

    pixt = pixaDisplayOnLattice(pixas, 100, 100);
    pixWrite("/tmp/junkpix.png", pixt, IFF_PNG);
    boxaWrite("/tmp/junkboxa.ba", pixas->boxa);
    pixDestroy(&pixt);
    pixaDestroy(&pixa);
    pixaDestroy(&pixas);
    pixaDestroy(&pixas2);
    boxaDestroy(&boxa);
#endif

    pixDestroy(&pixs);
    return 0;
}
