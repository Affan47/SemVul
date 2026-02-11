_print_job_num_nodes(job_info_t * job, int width, bool right_justify,
			 char* suffix)
{
	uint32_t node_cnt = 0;
	char tmp_char[8];

	if (job == NULL)
		_print_str("NODES", width, right_justify, true);
	else {
		if(params.cluster_flags & CLUSTER_FLAG_BG)
			select_g_select_jobinfo_get(job->select_jobinfo,
						    SELECT_JOBDATA_NODE_CNT,
						    &node_cnt);

		if ((node_cnt == 0) || (node_cnt == NO_VAL))
			node_cnt = _get_node_cnt(job);

		if(params.cluster_flags & CLUSTER_FLAG_BG)
			convert_num_unit((float)node_cnt, tmp_char,
					 sizeof(tmp_char), UNIT_NONE);
		else
			snprintf(tmp_char, sizeof(tmp_char), "%d", node_cnt);

		_print_str(tmp_char, width, right_justify, true);
	}
	if (suffix)
		printf("%s", suffix);
	return SLURM_SUCCESS;
}
