hsk_model (const int *list, DATASET *dset)
{
    int i, err;
    int orig_nvar = dset->v;
    int *hsklist;
    MODEL hsk;

    if (dset->Z == NULL) {
	hsk.errcode = E_DATA;
	return hsk;
    }

    gretl_error_clear();


    hsk = lsq(list, dset, OLS, OPT_A);
    if (hsk.errcode) {
	return hsk;
    }


    err = get_hsk_weights(&hsk, dset);
    if (err) {
	hsk.errcode = err;
	return hsk;
    }


    hsklist = gretl_list_new(list[0] + 1);
    if (hsklist == NULL) {
	hsk.errcode = E_ALLOC;
	return hsk;
    }


    hsklist[1] = dset->v - 1;


    hsklist[2] = list[1];


    for (i=3; i<=hsklist[0]; i++) {
	hsklist[i] = list[i-1];
    }

    clear_model(&hsk);
    hsk = lsq(hsklist, dset, WLS, OPT_NONE);
    hsk.ci = HSK;

    dataset_drop_last_variables(dset, dset->v - orig_nvar);

    free(hsklist);

    return hsk;
}
