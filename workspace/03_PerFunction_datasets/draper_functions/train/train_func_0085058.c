matrix(int nrl, int nrh, int ncl, int nch)
{
    int i;
    float GPFAR * GPFAR * m;

    m = gp_alloc((nrh - nrl + 1) * sizeof(m[0]), "matrix rows");
    m -= nrl;

    for (i = nrl; i <= nrh; i++) {
	if (!(m[i] = gp_alloc((nch - ncl + 1) * sizeof(m[i][0]), NULL))) {
	    free_matrix(m, nrl, i - 1, ncl);
	    int_error(NO_CARET, "not enough memory to create matrix");
	    return NULL;
	}
	m[i] -= ncl;
    }
    return m;
}
