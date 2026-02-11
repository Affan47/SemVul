panel_append_special (int addvars,
				 DATASET *dset,
				 DATASET *addset,
				 gretlopt opt,
				 PRN *prn)
{
    int n = dset->n / dset->pd;
    int T = dset->pd;
    int k = dset->v;
    int tsdata;
    int i, j, s, p, t;
    int err = 0;

    if (addvars > 0 && dataset_add_series(dset, addvars)) {
	merge_error(_("Out of memory!\n"), prn);
	err = E_ALLOC;
    }

    tsdata = ((opt & OPT_T) || addset->n != n);

    for (i=1; i<addset->v && !err; i++) {
	int v = series_index(dset, addset->varname[i]);

	if (v >= k) {

	    v = k++;
	    strcpy(dset->varname[v], addset->varname[i]);
	    copy_varinfo(dset->varinfo[v], addset->varinfo[i]);
	}

	s = 0;
	for (j=0; j<n; j++) {

	    for (t=0; t<T; t++) {

		p = (tsdata)? t : j;
		dset->Z[v][s++] = addset->Z[i][p];
	    }
	}
    }

    return err;
}
