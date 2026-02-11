real_create_new_dataset (int nvar, int nobs,
					 gretlopt opt)
{
    DATASET *dset = datainfo_new();

    if (dset == NULL) return NULL;

    dset->v = nvar;
    dset->n = nobs;
    dset->Z = NULL;

    if (start_new_Z(dset, opt)) {
	free(dset);
	return NULL;
    }

    if (opt & OPT_M) {
	if (dataset_allocate_obs_markers(dset)) {
	    free_datainfo(dset);
	    return NULL;
	}
    }

    dataset_obs_info_default(dset);

    return dset;
}
