maybe_expand_daily_data (DATASET *dset)
{
    int nmiss = n_hidden_missing_obs(dset);
    int err = 0;

    fprintf(stderr, "n_hidden_missing_obs: nmiss = %d\n", nmiss);

    if (nmiss < 0) {
	err = 1;
    } else if (nmiss > 0) {
	err = insert_missing_hidden_obs(dset, nmiss);
    }

    return err;
}
