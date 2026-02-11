nonlinearity_test (MODEL *pmod, DATASET *dset, ModelAuxCode aux,
		       gretlopt opt, PRN *prn)
{
    int save_t1 = dset->t1;
    int save_t2 = dset->t2;
    int *tmplist = NULL;
    const int orig_nvar = dset->v;
    int err = 0;

    if (!command_ok_for_model(ADD, 0, pmod->ci)) {
	return E_NOTIMP;
    }

    if (pmod->ci == LOGISTIC || pmod->ci == LAD) {
	return E_NOTIMP;
    }


    err = list_members_replaced(pmod->list, dset, pmod->ID);
    if (err) {
	return err;
    }


    impose_model_smpl(pmod, dset);


    tmplist = augment_regression_list(pmod->list, aux, dset, &err);
    if (err) {
	return err;
    } else if (tmplist[0] == pmod->list[0]) {

	if (aux == AUX_SQ) {
	    fprintf(stderr, "gretl: generation of squares failed\n");
	    err = E_SQUARES;
	} else if (aux == AUX_LOG) {
	    fprintf(stderr, "gretl: generation of logs failed\n");
	    err = E_LOGS;
	}
    }

    if (!err) {
	err = real_nonlinearity_test(pmod, tmplist, dset, aux,
				     opt, prn);
    }


    dataset_drop_last_variables(dset, dset->v - orig_nvar);


    dset->t1 = save_t1;
    dset->t2 = save_t2;

    free(tmplist);

    return err;
}
