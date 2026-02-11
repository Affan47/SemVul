gmm_recompute_weights (nlspec *s)
{
    gretl_matrix *W = s->oc->W;
    int err = 0;

    if (using_HAC(s)) {
	err = gmm_HAC(s->oc->tmp, W, &s->oc->hinfo);
    } else {
	err = gretl_matrix_multiply_mod(s->oc->tmp, GRETL_MOD_TRANSPOSE,
					s->oc->tmp, GRETL_MOD_NONE,
					W, GRETL_MOD_NONE);
    }

    if (!err) {
	gretl_matrix_divide_by_scalar(W, s->nobs);
	err = gretl_invert_symmetric_matrix(W);
    }

    return err;
}
