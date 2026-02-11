seasonally_adjust_series (const double *x, double *y,
			      DATASET *dset, int tramo,
			      int use_log)
{
    void *handle;
    int (*adjust_series) (const double *, double *,
			  const DATASET *, int, int);
    int t1 = dset->t1;
    int t2 = dset->t2;
    int T, err = 0;

    if (!quarterly_or_monthly(dset)) {
	gretl_errmsg_set(_("Input must be a monthly or quarterly time series"));
	return E_PDWRONG;
    }

    series_adjust_sample(x, &t1, &t2);
    T = t2 - t1 + 1;

    if (T < dset->pd * 3) {
	return E_TOOFEW;
    } else if (tramo && T > 600) {
	gretl_errmsg_set(_("TRAMO can't handle more than 600 observations.\n"
			   "Please select a smaller sample."));
	return E_EXTERNAL;
    } else if (!tramo) {
	int pdmax = get_x12a_maxpd();

	if (T > 50 * pdmax) {
	    gretl_errmsg_sprintf(_("X-12-ARIMA can't handle more than %d observations.\n"
				   "Please select a smaller sample."), 50 * pdmax);
	    return E_EXTERNAL;
	}
    }

    gretl_error_clear();

    adjust_series = get_plugin_function("adjust_series", &handle);

    if (adjust_series == NULL) {
	err = E_FOPEN;
    } else {
	int save_t1 = dset->t1;
	int save_t2 = dset->t2;

	dset->t1 = t1;
	dset->t2 = t2;

	err = (*adjust_series) (x, y, dset, tramo, use_log);

	dset->t1 = save_t1;
	dset->t2 = save_t2;

	close_plugin(handle);
    }

    return err;
}
