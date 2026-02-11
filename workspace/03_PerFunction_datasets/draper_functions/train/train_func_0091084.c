update_case_markers (const DATASET *dset)
{
    int err = 0;

    if (dset->markers && !fullset->markers) {
	dataset_allocate_obs_markers(fullset);
	if (fullset->S == NULL) {
	    err = 1;
	} else {
	    int t, subt = 0;

	    for (t=0; t<fullset->n; t++) {
		if (dset->submask[t]) {
		    strcpy(fullset->S[t], dset->S[subt++]);
		} else {
		    sprintf(fullset->S[t], "%d", t + 1);
		}
	    }
	}
    }

    return err;
}
