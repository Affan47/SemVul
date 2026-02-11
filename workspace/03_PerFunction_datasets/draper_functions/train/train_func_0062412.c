pdist_check_input (int dist, const double *parm,
			      double x)
{
    int i, np = 1;

    if (na(x)) {
	return E_MISSDATA;
    }

    if (dist == D_NORMAL) {
	np = 0;
    } else if (dist == D_SNEDECOR || dist == D_GAMMA ||
	       dist == D_BINOMIAL || dist == D_WEIBULL) {
	np = 2;
    } else if (dist == D_JOHANSEN || dist == D_BETABIN) {
	np = 3;
    }

    for (i=0; i<np; i++) {
	if (na(parm[i])) {
	    return E_MISSDATA;
	}
    }

    return 0;
}
