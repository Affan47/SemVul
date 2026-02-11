xgene_phy_xlate(struct device *dev,
				   struct of_phandle_args *args)
{
	struct xgene_phy_ctx *ctx = dev_get_drvdata(dev);

	if (args->args_count <= 0)
		return ERR_PTR(-EINVAL);
	if (args->args[0] < MODE_SATA || args->args[0] >= MODE_MAX)
		return ERR_PTR(-EINVAL);

	ctx->mode = args->args[0];
	return ctx->phy;
}
