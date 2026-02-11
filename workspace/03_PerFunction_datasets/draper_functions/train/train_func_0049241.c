list_makediscrete (const int *list, DATASET *dset, gretlopt opt)
{
    int disc = !(opt & OPT_R);
    int i, v, err = 0;

    for (i=1; i<=list[0]; i++) {
	v = list[i];
	if (v > 0) {
	    series_set_discrete(dset, v, disc);
	}
    }

    return err;
}
