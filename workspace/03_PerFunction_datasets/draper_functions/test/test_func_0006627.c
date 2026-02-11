change_file_list_metrics_check(change::pointer cp)
{
    size_t          j;
    fstate_src_ty   *src_data;

    for (j = 0; ; ++j)
    {
	metric_list_ty  *mlp;

	src_data = change_file_nth(cp, j, view_path_first);
	if (!src_data)
	    break;


	if (candidate(src_data))
	    continue;


	mlp = change_file_metrics_get(cp, src_data->file_name);


	metric_list_type.free(mlp);
    }
}
