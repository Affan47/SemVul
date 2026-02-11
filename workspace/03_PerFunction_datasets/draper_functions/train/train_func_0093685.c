dataset_get_structure (const DATASET *dset)
{
    if (dset == NULL || dset->n == 0) {
	return DATA_NONE;
    } else if (dataset_is_panel(dset)) {
	return DATA_PANEL;
    } else if (dataset_is_time_series(dset)) {
	return DATA_TS;
    } else {
	return DATA_XSECT;
    }
}
