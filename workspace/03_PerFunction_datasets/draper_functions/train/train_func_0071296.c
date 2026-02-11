union_pw_multi_aff_scale_multi_val_entry(void **entry, void *user)
{
	struct isl_union_pw_multi_aff_scale_multi_val_data *data = user;
	isl_pw_multi_aff *pma = *entry;

	if (!pma)
		return -1;
	if (!isl_space_tuple_match(pma->dim, isl_dim_out,
				    data->mv->space, isl_dim_set))
		return 0;

	pma = isl_pw_multi_aff_copy(pma);
	pma = isl_pw_multi_aff_scale_multi_val(pma,
						isl_multi_val_copy(data->mv));
	data->res = isl_union_pw_multi_aff_add_pw_multi_aff(data->res, pma);
	if (!data->res)
		return -1;

	return 0;
}
