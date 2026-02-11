butterworth_gain (int n, double cutoff, int hipass)
{
    gretl_matrix *G;
    int i, width = 180;
    double inc = M_PI / width;
    double x, gain, omega = 0.0;

    G = gretl_matrix_alloc(width + 1, 2);
    if (G == NULL) {
	return NULL;
    }

    for (i=0; i<=width; i++) {
	if (hipass) {
	    x = cotan(omega / 2) * cotan((M_PI - cutoff) / 2);
	} else {
	    x = tan(omega / 2) * cotan(cutoff / 2);
	}
	gain = 1 / (1 + pow(x, 2 * n));
	gretl_matrix_set(G, i, 0, omega);
	gretl_matrix_set(G, i, 1, gain);
	omega += inc;
    }

    return G;
}
