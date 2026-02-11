ntodate (char *datestr, int t, const DATASET *dset)
{
    double x;

#if 0
    fprintf(stderr, "real_ntodate: t=%d, pd=%d, sd0=%g\n",
	    t, dset->pd, dset->sd0);
#endif

    if (calendar_data(dset)) {

	if (dataset_has_markers(dset)) {
	    strcpy(datestr, dset->S[t]);
	} else {
	    calendar_date_string(datestr, t, dset);
	}
	return datestr;
    } else if (dataset_is_daily(dset) ||
	       dataset_is_weekly(dset)) {

	x = date_as_double(t, 1, dset->sd0);
	sprintf(datestr, "%d", (int) x);
	return datestr;
    } else if (dataset_is_decennial(dset)) {
	x = dset->sd0 + 10 * t;
	sprintf(datestr, "%d", (int) x);
	return datestr;
    } else if (dataset_is_panel(dset)) {
	panel_obs(datestr, t, dset);
	return datestr;
    }

    x = date_as_double(t, dset->pd, dset->sd0);

    if (dset->pd == 1) {
        sprintf(datestr, "%d", (int) x);
    } else {
	int pdp = dset->pd, len = 1;
	char fmt[8];

	while ((pdp = pdp / 10)) len++;
	sprintf(fmt, "%%.%df", len);
	sprintf(datestr, fmt, x);
	colonize_obs(datestr);
    }

    return datestr;
}
