skl_set_dsp_D0(struct sst_dsp *ctx)
{
	int ret;

	ret = skl_load_base_firmware(ctx);
	if (ret < 0) {
		dev_err(ctx->dev, "unable to load firmware\n");
		return ret;
	}

	skl_dsp_set_state_locked(ctx, SKL_DSP_RUNNING);

	return ret;
}
