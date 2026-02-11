qr_make_hac (MODEL *pmod, const DATASET *dset,
			gretl_matrix *XTXi)
{
    gretl_matrix *X, *XOX, *V = NULL;
    gretl_matrix umat;
    VCVInfo vi;
    int T = pmod->nobs;
    int err = 0;

    X = make_data_X(pmod, dset);
    if (X == NULL) {
	return E_ALLOC;
    }


    gretl_matrix_init(&umat);
    umat.rows = T;
    umat.cols = 1;
    umat.val = pmod->uhat + pmod->t1;

    XOX = HAC_XOX(&umat, X, &vi, &err);

    if (!err) {
	V = gretl_matrix_alloc(XOX->rows, XOX->rows);
	if (V == NULL) {
	    err = E_ALLOC;
	}
    }

    if (!err) {
	gretl_matrix_qform(XTXi, GRETL_MOD_TRANSPOSE, XOX,
			   V, GRETL_MOD_NONE);

	err = qr_make_vcv(pmod, V, VCV_ROBUST);
    }

    if (!err) {
	gretl_model_set_full_vcv_info(pmod, vi.vmaj, vi.vmin,
				      vi.order, vi.flags,
				      vi.bw);
    }

    gretl_matrix_free(X);
    gretl_matrix_free(XOX);
    gretl_matrix_free(V);

    return err;
}
