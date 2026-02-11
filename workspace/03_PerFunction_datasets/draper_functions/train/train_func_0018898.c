do_restricted_ols (boot *bs)
{
    double s2 = 0.0;
    int err = 0;

    err = gretl_matrix_restricted_ols(bs->y, bs->X, bs->R, bs->q, bs->b0,
				      NULL, bs->u0, &s2);

#if BDEBUG
    if (1) {
	int i;

	fprintf(stderr, "Restricted estimates (err = %d):\n", err);
	for (i=0; i<bs->b0->rows; i++) {
	    fprintf(stderr, "b[%d] = %g\n", i, bs->b0->val[i]);
	}
	fprintf(stderr, "s2 = %g\n", s2);
    }
#endif

    if (!err) {
	bs->SE = sqrt(s2);
    }

    return err;
}
