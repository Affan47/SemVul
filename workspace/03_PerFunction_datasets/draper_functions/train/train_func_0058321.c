doubles_array_adjust_length (double **X, int m, int new_n)
{
    int err = 0;

    if (X == NULL || m == 0) {
	;
    } else {
	double *xi;
	int i;

	for (i=0; i<m && !err; i++) {
	    if (new_n == 0) {
		free(X[i]);
		X[i] = NULL;
	    } else {
		xi = realloc(X[i], new_n * sizeof *xi);
		if (xi == NULL) {
		    err = E_ALLOC;
		} else {
		    X[i] = xi;
		}
	    }
	}
    }

    return err;
}
