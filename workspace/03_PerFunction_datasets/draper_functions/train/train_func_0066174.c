lg4573_init(struct lg4573 *ctx)
{
	int ret;

	dev_dbg(ctx->panel.dev, "initializing LCD\n");

	ret = lg4573_display_mode_settings(ctx);
	if (ret)
		return ret;

	ret = lg4573_power_settings(ctx);
	if (ret)
		return ret;

	return lg4573_gamma_settings(ctx);
}
