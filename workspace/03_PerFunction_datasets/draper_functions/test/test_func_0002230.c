ivreg_oc_setup (nlspec *spec, const int *ilist,
			   MODEL *pmod, DATASET *dset,
			   int *rv)
{
    int v = dset->v;
    int i, err;


    err = dataset_add_series(dset, 1);

    if (!err) {
	*rv = v;
	strcpy(dset->varname[v], IVREG_RESIDNAME);
	for (i=0; i<dset->n; i++) {
	    dset->Z[v][i] = pmod->uhat[i];
	}
	err = nlspec_add_ivreg_oc(spec, v, ilist, (const double **) dset->Z);
    }

    return err;
}
