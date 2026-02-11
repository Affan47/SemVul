wishart_workspace (gretl_matrix **pW,
			      gretl_matrix **pB,
			      double **pZ,
			      int p)
{
    int err = 0;

    *pW = gretl_matrix_alloc(p, p);

    if (*pW == NULL) {
	return E_ALLOC;
    }

    *pB = gretl_matrix_alloc(p, p);

    if (*pB == NULL) {
	err = E_ALLOC;
    } else {
	int n = p * (p + 1) / 2;

	*pZ = malloc(n * sizeof **pZ);
	if (*pZ == NULL) {
	    err = E_ALLOC;
	} else {
	    gretl_rand_normal(*pZ, 0, n - 1);
	}
    }

    if (err) {
	gretl_matrix_free(*pW);
	gretl_matrix_free(*pB);
    }

    return err;
}
