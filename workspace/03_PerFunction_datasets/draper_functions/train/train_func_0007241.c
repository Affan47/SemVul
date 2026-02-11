generate_sorted_domains_wrap(__isl_take isl_basic_set_list *scc,
	void *user)
{
	struct isl_ast_generate_parallel_domains_data *data = user;
	isl_ast_graft_list *list;

	list = generate_sorted_domains(scc, data->executed, data->build);
	data->single = isl_basic_set_list_n_basic_set(scc) == data->n;
	if (!data->single)
		list = isl_ast_graft_list_fuse(list, data->build);
	if (!data->list)
		data->list = list;
	else
		data->list = isl_ast_graft_list_concat(data->list, list);

	isl_basic_set_list_free(scc);
	if (!data->list)
		return -1;

	return 0;
}
