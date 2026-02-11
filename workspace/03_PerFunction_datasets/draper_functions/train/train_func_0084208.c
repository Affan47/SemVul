set_contiguous_sample (const int *list,
				  DATASET *dset,
				  gretlopt opt)
{
    int save_t1 = dset->t1;
    int save_t2 = dset->t2;
    int err = 0;

    if (opt & OPT_P) {

	return E_BADOPT;
    }

    if (list != NULL && list[0] > 0) {
	err = list_adjust_sample(list, &dset->t1, &dset->t2, dset, NULL);
    } else {
	int *biglist = NULL;
	int nvars = 0;

	biglist = full_var_list(dset, &nvars);
	if (nvars == 0) {
	    ;
	} else if (biglist == NULL) {
	    err = E_ALLOC;
	} else {
	    err = list_adjust_sample(biglist, &dset->t1, &dset->t2,
				     dset, NULL);
	    free(biglist);
	}
    }

    if (err) {
	dset->t1 = save_t1;
	dset->t2 = save_t2;
    }

    return err;
}
