sAdjust(void)
{
    int iterCnt = 0;
    int overlapCnt = 0;
    int cnt;
    Point center;


    if (!useIter || (iterations > 0))
	overlapCnt = countOverlap(iterCnt);

    if ((overlapCnt == 0) || (iterations == 0))
	return 0;

    rmEquality();
    center.x = (pxmin + pxmax) / 2.0;
    center.y = (pymin + pymax) / 2.0;
    while (1) {
	 rePos(center);
	iterCnt++;

	if (useIter && (iterCnt == iterations))
	    break;
	cnt = countOverlap(iterCnt);
	if (cnt == 0)
	    break;
    }

    if (Verbose) {
	fprintf(stderr, "Number of iterations = %d\n", iterCnt);
    }

    return 1;
}
