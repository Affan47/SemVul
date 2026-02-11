count_model (const int *list, int ci, DATASET *dset,
		   gretlopt opt, PRN *prn)
{
    MODEL cmod;
    void *handle;
    int *listcpy;
    int offvar;
    int (* count_data_estimate) (MODEL *, int, int,
				 DATASET *, gretlopt,
				 PRN *);

    gretl_error_clear();

    gretl_model_init(&cmod, dset);

    if (!gretl_iscount(dset->t1, dset->t2, dset->Z[list[1]])) {
	gretl_errmsg_sprintf(_("%s: the dependent variable must be count data"),
			     gretl_command_word(ci));
	cmod.errcode = E_DATA;
	return cmod;
    }

    listcpy = gretl_list_copy(list);
    if (listcpy == NULL) {
	cmod.errcode = E_ALLOC;
        return cmod;
    }

    offvar = get_trailing_var(listcpy);


    cmod = lsq(listcpy, dset, OLS, OPT_A);
    free(listcpy);

    if (cmod.errcode) {
        return cmod;
    }

    count_data_estimate = get_plugin_function("count_data_estimate",
					      &handle);

    if (count_data_estimate == NULL) {
	cmod.errcode = E_FOPEN;
	return cmod;
    }

    (*count_data_estimate) (&cmod, ci, offvar, dset, opt, prn);

    close_plugin(handle);

    set_model_id(&cmod);

    return cmod;
}
