get_subperiod (int t, const DATASET *dset, int *err)
{
    int ret = 0;

    if (!dataset_is_seasonal(dset)) {
	if (err != NULL) {
	    *err = E_PDWRONG;
	}
	return 0;
    }

    if (dataset_is_weekly(dset)) {

	ret = t % dset->pd;
    } else if (calendar_data(dset)) {

	char datestr[12];

	calendar_date_string(datestr, t, dset);
	ret = weekday_from_date(datestr);
    } else if (dataset_is_daily(dset)) {

	ret = t % dset->pd;
    } else {

	double x = date_as_double(t, dset->pd, dset->sd0);
	int i, d = ceil(log10(dset->pd));

	x -= floor(x);
	for (i=0; i<d; i++) {
	    x *= 10;
	}
	ret = xround(x) - 1;
    }

    return ret;
}
