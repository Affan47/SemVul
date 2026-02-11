clear_datainfo (DATASET *dset, int code)
{
    int i;

    if (dset == NULL) return;

    if (dset->S != NULL) {
	dataset_destroy_obs_markers(dset);
    }

    if (dset->submask != NULL) {
	free_subsample_mask(dset->submask);
	dset->submask = NULL;
    }

    if (dset->restriction != NULL) {
	free(dset->restriction);
	dset->restriction = NULL;
    }

    if (dset->padmask != NULL) {
	free(dset->padmask);
	dset->padmask = NULL;
    }

    if (dset->pangrps != NULL) {
	free(dset->pangrps);
	dset->pangrps = NULL;
    }


    if (code == CLEAR_FULL) {
	if (dset->varname != NULL) {
	    for (i=0; i<dset->v; i++) {
		free(dset->varname[i]);
	    }
	    free(dset->varname);
	    dset->varname = NULL;
	}
	if (dset->varinfo != NULL) {
	    for (i=0; i<dset->v; i++) {
		free_varinfo(dset, i);
	    }
	    free(dset->varinfo);
	    dset->varinfo = NULL;
	}
	if (dset->descrip != NULL) {
	    free(dset->descrip);
	    dset->descrip = NULL;
	}

	maybe_free_full_dataset(dset);

	dset->v = dset->n = 0;
    }
}
