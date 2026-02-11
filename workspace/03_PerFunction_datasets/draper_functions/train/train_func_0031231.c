qr_make_hccme (MODEL *pmod, const DATASET *dset,
			  gretl_matrix *Q, gretl_matrix *XTXi)
{
    gretl_matrix *X;
    gretl_matrix *diag = NULL;
    gretl_matrix *tmp1 = NULL, *tmp2 = NULL, *vcv = NULL;
    int T = pmod->nobs;
    int k = pmod->list[0] - 1;
    int hc_version;
    int i, t;
    int err = 0;

    X = make_data_X(pmod, dset);
    if (X == NULL) return 1;

    diag = gretl_vector_from_array(pmod->uhat + pmod->t1, T,
				   GRETL_MOD_SQUARE);
    if (diag == NULL) {
	err = 1;
	goto bailout;
    }

    tmp1 = gretl_matrix_alloc(k, T);
    tmp2 = gretl_matrix_alloc(k, k);
    vcv = gretl_matrix_alloc(k, k);
    if (tmp1 == NULL || tmp2 == NULL || vcv == NULL) {
	err = 1;
	goto bailout;
    }

    hc_version = libset_get_int(HC_VERSION);
    gretl_model_set_vcv_info(pmod, VCV_HC, hc_version);

    if (hc_version == 1) {
	for (t=0; t<T; t++) {
	    diag->val[t] *= (double) T / (T - k);
	}
    } else if (hc_version > 1) {

	for (t=0; t<T; t++) {
	    double q, ht = 0.0;

	    for (i=0; i<k; i++) {
		q = gretl_matrix_get(Q, t, i);
		ht += q * q;
	    }
	    if (hc_version == 2) {
		diag->val[t] /= (1.0 - ht);
	    } else {
		diag->val[t] /= (1.0 - ht) * (1.0 - ht);
	    }
	}
    }

    do_X_prime_diag(X, diag, tmp1);
    gretl_matrix_multiply(tmp1, X, tmp2);
    gretl_matrix_qform(XTXi, GRETL_MOD_NONE, tmp2,
		       vcv, GRETL_MOD_NONE);


    err = qr_make_vcv(pmod, vcv, VCV_ROBUST);

 bailout:

    gretl_matrix_free(X);
    gretl_matrix_free(diag);
    gretl_matrix_free(tmp1);
    gretl_matrix_free(tmp2);
    gretl_matrix_free(vcv);

    return err;
}
