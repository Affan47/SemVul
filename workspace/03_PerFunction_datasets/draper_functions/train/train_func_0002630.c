gth_file_data_cmp_date_time_original (GthFileData *a,
				      GthFileData *b)
{
	GTimeVal *pta, *ptb;
	GTimeVal  ta, tb;
	int       result;

	pta = NULL;
	if (gth_file_data_get_digitalization_time (a, &ta))
		pta = &ta;
	if (pta == NULL)
		pta = gth_file_data_get_modification_time (a);

	ptb = NULL;
	if (gth_file_data_get_digitalization_time (b, &tb))
		ptb = &tb;
	if (ptb == NULL)
		ptb = gth_file_data_get_modification_time (b);

	result = _g_time_val_cmp (pta, ptb);
	if (result == 0) {
		const char *key_a, *key_b;

		key_a = gth_file_data_get_filename_sort_key (a);
		key_b = gth_file_data_get_filename_sort_key (b);

		result = strcmp (key_a, key_b);
	}

	return result;
}
