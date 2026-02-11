rank3(graph_t * g, aspect_t * asp)
{
    Agnode_t *n;
    int i;
    int iterations = asp->nextIter;
    double lastAR = MAXDOUBLE;

    computeNodeGroups(g);

    for (i = 0; (i < iterations) || (iterations == -1); i++) {

	for (n = agfstnode(g); n; n = agnxtnode(g, n)) {
	    ND_rank(n) = 0;
	}


	rank1(g);

	asp->combiAR = computeCombiAR(g);
	if (Verbose)
	    fprintf(stderr, "combiAR = %lf\n", asp->combiAR);


#ifdef UNUSED
	if (combiAR < 0.8 * targetAR) {
	    char str[20];
	    printf("Apply expansion? (y/n):");
	    scanf("%s", str);
	    if (strcmp(str, "y") == 0)
		applyExpansion(g);
	    break;
	} else
#endif

	if ((asp->combiAR <= asp->targetAR) || ((iterations == -1) && (lastAR <= asp->combiAR))) {
	    asp->prevIterations = asp->curIterations;
	    asp->curIterations = i;

	    break;
	}
	lastAR = asp->combiAR;

	applyPacking2(g);
    }


    rank1(g);

    computeLayerWidths(g);
    zapLayers(g);
    asp->combiAR = computeCombiAR(g);
}
