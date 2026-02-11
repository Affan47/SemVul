copy_data_to_subsample (DATASET *subset, const DATASET *dset,
			int maxv, const char *mask)
{
    int i, t, s;

#if SUBDEBUG
    fprintf(stderr, "copy_data_to_subsample: subset = %p, dset = %p\n",
	    (void *) subset, (void *) dset);
#endif


    for (i=1; i<maxv; i++) {
	s = 0;
	for (t=0; t<dset->n; t++) {
	    if (mask == NULL) {
		subset->Z[i][s++] = dset->Z[i][t];
	    } else if (mask[t] == 1) {
		subset->Z[i][s++] = dset->Z[i][t];
	    } else if (mask[t] == 'p') {

		subset->Z[i][s++] = NADBL;
	    }
	}
    }


    if (dset->markers && subset->markers) {
	s = 0;
	for (t=0; t<dset->n; t++) {
	    if (mask == NULL || mask[t] == 1 || mask[t] == 'p') {
		strcpy(subset->S[s++], dset->S[t]);
	    }
	}
    }


    if (dataset_is_panel(subset)) {
	if (subset->pd == dset->pd) {
	    subset->panel_pd = dset->panel_pd;
	    subset->panel_sd0 = dset->panel_sd0;
	}
    }

    strcpy(subset->stobs, "1");
    sprintf(subset->endobs, "%d", subset->n);
}
