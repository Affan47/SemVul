n_hidden_missing_obs (const DATASET *dset)
{
    int t1, t2;
    int cal_n;

    if (!dated_daily_data(dset) || dset->S == NULL) {
	return 0;
    }

    t1 = calendar_obs_number(dset->S[0], dset);
    t2 = calendar_obs_number(dset->S[dset->n - 1], dset);

    cal_n = t2 - t1 + 1;

    return cal_n - dset->n;
}
