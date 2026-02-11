mle_llt_callback (const double *b, int i, void *p)
{
    nlspec *s = (nlspec *) p;
    int err;

    update_coeff_values(b, s);
    err = nl_calculate_fvec(s);

    if (err) {
	return NULL;
    } else if (s->lhtype == GRETL_TYPE_MATRIX) {
	s->lvec = get_matrix_by_name(s->lhname);
	if (s->lvec == NULL) {
	    fprintf(stderr, "mle_llt_callback: s->lvec is gone!\n");
	    return NULL;
	} else {
	    return s->lvec->val;
	}
    } else {
	return s->dset->Z[s->lhv] + s->t1;
    }
}
