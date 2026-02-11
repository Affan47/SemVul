mband_reduce(FILE *inf, FILE *outf)
{
	struct mband_dataset *mbds;

	mbds = mband_dataset_new();
	g_return_val_if_fail(mbds != NULL, -1);
	mband_dataset_set_ubvri(mbds);


	mband_dataset_release(mbds);
	return 0;
}
