write_esl_lbl (const char *lblfile, const int *list,
			  const DATASET *dset)
{
    int i, vi, labels = 0;
    int err = 0;

    for (i=1; i<=list[0]; i++) {
	vi = list[i];
	if (vi != 0 && strlen(series_get_label(dset, vi)) > 2) {
	    labels = 1;
	    break;
	}
    }

    if (labels) {
	FILE *fp = gretl_fopen(lblfile, "w");

	if (fp == NULL) {
	    err = E_FOPEN;
	} else {

	    for (i=1; i<=list[0]; i++) {
		vi = list[i];
		if (vi != 0 && strlen(series_get_label(dset, vi)) > 2) {
		    fprintf(fp, "%s %s\n", dset->varname[vi],
			    series_get_label(dset, vi));
		}
	    }
	    fclose(fp);
	}
    }

    return err;
}
