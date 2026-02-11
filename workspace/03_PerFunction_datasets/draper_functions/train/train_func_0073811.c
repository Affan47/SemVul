camAllocateMatrix(int nrl, int nrh, int ncl, int nch)
{
    int i;
    double **m;

    m=(double **)malloc((unsigned)(nrh - nrl + 1)*sizeof(double*));
    if (!m) {
	camError("camAllocateMatrix", "Memory allocation failure");
	return NULL;
    }
    m -= nrl;

    for(i = nrl; i <= nrh; i++) {
	m[i]=(double *)malloc((unsigned)(nch - ncl + 1)*sizeof(double));
	if (!m[i]) {
	    camError("camAllocateMatrix", "Memory allocation failure");
	    return NULL;
	}
	m[i] -= ncl;
    }
    return m;
}
