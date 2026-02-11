emitSpline (char* s, FILE* outFile, int ix)
{
    double sx, sy, ex, ey;
    int sarrow = 0;
    int earrow = 0;

    s = arrowEnd (s, "e,", &earrow, &ex, &ey);
    s = arrowEnd (s, "s,", &sarrow, &sx, &sy);
    indent (ix, outFile);
    fprintf (outFile, "Line [\n");
    if (sarrow)
	emitPoint (sx, sy, outFile, ix+1);
    while ((s = readPoint (s, &sx, &sy)))
	emitPoint (sx, sy, outFile, ix+1);
    if (earrow)
	emitPoint (ex, ey, outFile, ix+1);
    indent (ix, outFile);
    fprintf (outFile, "]\n");

}
