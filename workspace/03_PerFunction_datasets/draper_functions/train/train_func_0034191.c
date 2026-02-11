print_y_data (const double *x,
			  const double *y,
			  const int *order,
			  int t0, int t1, int t2,
			  FILE *fp)
{
    int i, t, n = t2 - t0 + 1;
    double xt;

    for (i=0; i<n; i++) {
	if (order != NULL) {
	    t = order[i];
	    xt = i + 1;
	} else {
	    t = t0 + i;
	    xt = x[t];
	}
	if (t < t1 || na(y[t])) {
	    fprintf(fp, "%.10g ?\n", xt);
	} else {
	    fprintf(fp, "%.10g %.10g\n", xt, y[t]);
	}
    }

    fputs("e\n", fp);
}
