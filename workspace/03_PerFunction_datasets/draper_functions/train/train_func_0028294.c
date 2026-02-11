__fimc_pipeline_open(struct exynos_media_pipeline *ep,
				struct media_entity *me, bool prepare)
{
	struct fimc_md *fmd = entity_to_fimc_mdev(me);
	struct fimc_pipeline *p = to_fimc_pipeline(ep);
	struct v4l2_subdev *sd;
	int ret;

	if (WARN_ON(p == NULL || me == NULL))
		return -EINVAL;

	if (prepare)
		fimc_pipeline_prepare(p, me);

	sd = p->subdevs[IDX_SENSOR];
	if (sd == NULL)
		return -EINVAL;


	if (!IS_ERR(fmd->wbclk[CLK_IDX_WB_B]) && p->subdevs[IDX_IS_ISP]) {
		ret = clk_prepare_enable(fmd->wbclk[CLK_IDX_WB_B]);
		if (ret < 0)
			return ret;
	}

	ret = fimc_pipeline_s_power(p, 1);
	if (!ret)
		return 0;

	if (!IS_ERR(fmd->wbclk[CLK_IDX_WB_B]) && p->subdevs[IDX_IS_ISP])
		clk_disable_unprepare(fmd->wbclk[CLK_IDX_WB_B]);

	return ret;
}
