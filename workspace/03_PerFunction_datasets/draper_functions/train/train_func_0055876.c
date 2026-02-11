dot_Ivector(Imatrix M1, Imatrix M2)
{
    int k, d = 0;
    if (M1 == 0 || M2 == 0 || ImatrixMcols(M1) != ImatrixMcols(M2)) {
#ifdef LOG_PRINT
	fprintf(stderr, "dot_Ivector: incompatible or null vectors\n")
#endif
;
	return 0;
    }
    for (k = 1; k <= ImatrixMcols(M1); k++)
	d += ImatrixVref(M1, k) * ImatrixVref(M2, k);
    return d;
}
