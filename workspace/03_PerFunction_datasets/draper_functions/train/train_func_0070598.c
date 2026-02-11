mean1d (sv1, sv2, mean, sigma)

double *sv1, *sv2;
double *mean;
double *sigma;
{
    double *sv;
    double p, pmin, pmax, pmean;
    double sd;
    int i;
    int npix;
    double dnpix;
    double sum;

    pmin = -1.0e20;
    pmax = 1.0e20;


    for (i = 0; i < niterate; i++ ) {
	npix = 0;
	sum = 0.0;


	for (sv = sv1; sv < sv2; sv++) {
	    p = *sv;
	    if (p > pmin && p < pmax) {
		sum += p;
		npix++;
		}
	    }
	if (npix > 0) {
	    dnpix = (double) npix;
	    pmean = sum / dnpix;
	    }
	else
	    pmean = 0.0;


	npix = 0;
	sum = 0.0;
	for (sv = sv1; sv < sv2; sv++) {
	    p = *sv;
	    if (p > pmin && p < pmax) {
		sum += fabs (p - pmean);
		npix++;
		}
	    }
	if (npix > 0)
	    sd = sum / dnpix;
	else
	    sd = 0.0;
	pmin = pmean - (sd * starsig);
	pmax = pmean + (sd * starsig);
	}
    *mean = pmean;
    *sigma = sd;
    return;
}
