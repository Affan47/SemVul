gk20a_pmu_dvfs_get_target_state(struct gk20a_pmu *pmu,
				int *state, int load)
{
	struct gk20a_pmu_dvfs_data *data = pmu->data;
	struct nvkm_clk *clk = pmu->base.subdev.device->clk;
	int cur_level, level;


	level = cur_level = clk->pstate;

	if (load > data->p_load_max) {
		level = min(clk->state_nr - 1, level + (clk->state_nr / 3));
	} else {
		level += ((load - data->p_load_target) * 10 /
				data->p_load_target) / 2;
		level = max(0, level);
		level = min(clk->state_nr - 1, level);
	}

	nvkm_trace(&pmu->base.subdev, "cur level = %d, new level = %d\n",
		   cur_level, level);

	*state = level;

	if (level == cur_level)
		return 0;
	else
		return 1;
}
