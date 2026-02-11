setup_proc_scaling(void)
	{
	GkrellmChart	*cp		= proc.chart;
	gint			grids, res, new_fork_scaling;

	if (!cp)
		return;

	grids = gkrellm_get_chartconfig_fixed_grids(cp->config);
	if (!grids)
		grids = FULL_SCALE_GRIDS;

	res = gkrellm_get_chartconfig_grid_resolution(cp->config);


	KRELL(cp->panel)->full_scale = 10;

	new_fork_scaling = grids * res / 50;
	if (new_fork_scaling < 1)
		new_fork_scaling = 1;


	if (fork_scaling != new_fork_scaling)
		{


		gkrellm_scale_chartdata(proc.forks_cd, new_fork_scaling, fork_scaling);
		gkrellm_rescale_chart(proc.chart);
		}
	fork_scaling = new_fork_scaling;
	}
