cam_clk_prepare(struct clk_hw *hw)
{
	struct cam_clk *camclk = to_cam_clk(hw);
	int ret;

	if (camclk->fmd->pmf == NULL)
		return -ENODEV;

	ret = pm_runtime_get_sync(camclk->fmd->pmf);
	return ret < 0 ? ret : 0;
}
