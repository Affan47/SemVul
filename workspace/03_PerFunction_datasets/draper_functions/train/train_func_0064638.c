factorized_boxplot_check (const int *list,
				     char **bools,
				     const DATASET *dset)
{
    int err = 0;

    if (list[0] != 2 || bools != NULL) {
	err = E_DATA;
    } else {
	int v2 = list[2];

	if (!series_is_discrete(dset, v2) &&
	    !gretl_isdiscrete(dset->t1, dset->t2, dset->Z[v2])) {
	    gretl_errmsg_set(_("You must supply two variables, the second of "
			       "which is discrete"));
	    err = E_DATA;
	}
    }

    return err;
}
