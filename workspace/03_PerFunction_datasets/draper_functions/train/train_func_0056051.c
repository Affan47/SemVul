makevcv (MODEL *pmod, double sigma)
{
    int dec, mst, kk, i, j, kj, icnt, m, k, l = 0;
    int nv, nxpx;
    double d;

    if (pmod->vcv != NULL) {

	return 0;
    }

    if (pmod->xpx == NULL) {

	fprintf(stderr, "makevcv: pmod->xpx = NULL\n");
	return E_BADSTAT;
    }

    nv = pmod->ncoeff;
    nxpx = (nv * nv + nv) / 2;
    mst = nxpx;
    kk = nxpx - 1;

    pmod->vcv = malloc(nxpx * sizeof *pmod->vcv);
    if (pmod->vcv == NULL) {
	return E_ALLOC;
    }

    for (i=0; i<nv; i++) {
	mst -= i;

	d = pmod->xpx[kk];
	if (i > 0) {
	    for (j=kk+1; j<=kk+i; j++) {
		d -= pmod->xpx[j] * pmod->vcv[j];
	    }
	}
	pmod->vcv[kk] = d * pmod->xpx[kk];

	kj = kk;
	kk = kk - i - 2;
	if (i > nv - 2) {
	    continue;
	}
	for (j=i+1; j<nv; j++) {
	    icnt = i+1;
	    kj -= j;
	    d = 0.0;
	    m = mst + 1;
	    for (k=0; k<=j-1; k++) {
		if (icnt > 0) {
		    dec = 1;
		    icnt--;
		} else {
		    dec = k;
		}
		m -= dec;
		l = kj + i - k;
		d += pmod->vcv[m-1] * pmod->xpx[l];
	    }
	    pmod->vcv[kj] = -d * pmod->xpx[l-1];
	}
    }

    if (pmod->ci == LOGIT || pmod->ci == PROBIT) {
	sigma = 1.0;
    }

    if (sigma != 1.0) {
	double s2 = sigma * sigma;

	for (i=0; i<nxpx; i++) {
	    pmod->vcv[i] *= s2;
	}
    }

    return 0;
}
