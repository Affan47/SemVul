genr_fit_resid (const MODEL *pmod, DATASET *dset,
		    ModelDataIndex idx)
{
    char vname[VNAMELEN], vlabel[MAXLABEL];
    double *x;
    int err = 0;

    x = get_fit_or_resid(pmod, dset, idx, vname, vlabel, &err);

    if (!err) {
	err = dataset_add_allocated_series(dset, x);
    }

    if (err) {
	free(x);
    } else {
	int v = dset->v - 1;

	strcpy(dset->varname[v], vname);
	series_set_label(dset, v, vlabel);
    }

    return err;
}
