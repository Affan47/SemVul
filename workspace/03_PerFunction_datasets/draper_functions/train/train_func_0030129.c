gfarm_job_info_server_free_contents(struct gfarm_job_info *infos, int n)
{
	int i, j;
	struct gfarm_job_info *info;

	for (i = 0; i < n; i++) {
		info = &infos[i];


		free(info->job_type);
		free(info->originate_host);
		free(info->gfarm_url_for_scheduling);
		for (j = 0; j < info->argc; j++)
			free(info->argv[j]);
		free(info->argv);
		for (j = 0; j < info->total_nodes; j++)
			free(info->nodes[j].hostname);
		free(info->nodes);
	}
}
