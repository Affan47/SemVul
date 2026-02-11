pw_multi_aff_drop(__isl_take isl_pw_multi_aff *pma, void *user)
{
	struct isl_union_pw_multi_aff_drop_data *data = user;

	pma = isl_pw_multi_aff_drop_dims(pma, isl_dim_out, data->pos, data->n);

	data->res = isl_union_pw_multi_aff_add_pw_multi_aff(data->res, pma);
	if (!data->res)
		return -1;

	return 0;
}
