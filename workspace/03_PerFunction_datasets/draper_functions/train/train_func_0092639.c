qr_make_cluster_vcv (MODEL *pmod, int ci,
				const DATASET *dset,
				gretl_matrix *XX,
				gretlopt opt)
{
    gretl_matrix *cvals = NULL;
    gretl_matrix *V = NULL;
    const char *cname;
    int cvar, n_c = 0;
    int err = 0;

    if (pmod->ci != OLS && pmod->ci != IVREG) {

	return E_NOTIMP;
    }

    cname = get_optval_string(ci, OPT_C);
    if (cname == NULL) {
	return E_PARSE;
    }

    cvar = current_series_index(dset, cname);
    if (cvar < 1 || cvar >= dset->v) {
	err = E_UNKVAR;
    }

    if (!err) {
	cvals = cluster_var_values(dset->Z[cvar], pmod, &err);
	if (!err) {
	    n_c = gretl_vector_get_length(cvals);
	    if (n_c < 2) {
		err = E_DATA;
	    }
	}
    }

#if CDEBUG
    fprintf(stderr, "qr_make_cluster_vcv: err = %d\n", err);
    fprintf(stderr, "cluster var = %s (%d)\n", cname, cvar);
    gretl_matrix_print(cvals, "cvals");
#endif

    if (!err) {
	V = cluster_vcv_calc(pmod, cvar, cvals, XX, dset, &err);
    }

    if (!err) {
	err = gretl_model_write_vcv(pmod, V);
    }

    if (!err) {
	gretl_model_set_vcv_info(pmod, VCV_CLUSTER, cvar);
	gretl_model_set_int(pmod, "n_clusters", n_c);
    }

    gretl_matrix_free(V);
    gretl_matrix_free(cvals);

    return err;
}
