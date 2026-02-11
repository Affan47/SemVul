numerical_hessian_inverse (const double *b, int n,
					 BFGS_CRIT_FUNC func,
					 void *data, int *err)
{
    gretl_matrix *H = gretl_zero_matrix_new(n, n);

    if (H == NULL) {
	*err = E_ALLOC;
    } else {
	*err = numerical_hessian(b, H, func, data);
    }

    if (!*err) {
	*err = gretl_invert_symmetric_matrix(H);
	if (*err) {
	    fprintf(stderr, "numerical_hessian_inverse: failed\n");
	    gretl_errmsg_set(_("Failed to compute numerical Hessian"));
	    gretl_matrix_free(H);
	    H = NULL;
	}
    }

    return H;
}
