gretl_is_series (const char *name, const DATASET *dset)
{
    if (dset == NULL) {
	return 0;
    } else {
	int v = series_index(dset, name);

	return (v >= 0 && v < dset->v);
    }
}
