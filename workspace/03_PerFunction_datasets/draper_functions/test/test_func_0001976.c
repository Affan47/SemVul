bin_entry(void **entry, void *user)
{
	struct isl_union_pw_multi_aff_bin_data *data = user;
	isl_pw_multi_aff *pma = *entry;

	data->pma = pma;
	if (isl_hash_table_foreach(data->upma2->dim->ctx, &data->upma2->table,
				   data->fn, data) < 0)
		return -1;

	return 0;
}
