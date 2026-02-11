tool_random_engine_run_bernoulli (GOCmdContext *gcc, data_analysis_output_t *dao,
				  tools_data_random_t *info,
				  bernoulli_random_tool_t *param)
{
	int i, n;
	PROGRESS_START;
	for (i = 0; i < info->n_vars; i++) {
		for (n = 0; n < info->count; n++) {
			gnm_float tmp = random_bernoulli (param->p);
			dao_set_cell_int (dao, i, n, (int)tmp);
			PROGESS_RUN;
		}
	}
	PROGESS_END;
	return FALSE;
}
