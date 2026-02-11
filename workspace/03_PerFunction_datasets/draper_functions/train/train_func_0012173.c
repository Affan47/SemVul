fimc_capture_config_update(struct fimc_ctx *ctx)
{
	struct fimc_dev *fimc = ctx->fimc_dev;
	int ret;

	fimc_hw_set_camera_offset(fimc, &ctx->s_frame);

	ret = fimc_set_scaler_info(ctx);
	if (ret)
		return ret;

	fimc_hw_set_prescaler(ctx);
	fimc_hw_set_mainscaler(ctx);
	fimc_hw_set_target_format(ctx);
	fimc_hw_set_rotation(ctx);
	fimc_hw_set_effect(ctx);
	fimc_prepare_dma_offset(ctx, &ctx->d_frame);
	fimc_hw_set_out_dma(ctx);
	if (fimc->drv_data->alpha_color)
		fimc_hw_set_rgb_alpha(ctx);

	clear_bit(ST_CAPT_APPLY_CFG, &fimc->state);
	return ret;
}
