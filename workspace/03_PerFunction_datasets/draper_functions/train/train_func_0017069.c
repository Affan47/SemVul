xgene_phy_hw_init(struct phy *phy)
{
	struct xgene_phy_ctx *ctx = phy_get_drvdata(phy);
	int rc;
	int i;

	rc = xgene_phy_hw_initialize(ctx, CLK_EXT_DIFF, SSC_DISABLE);
	if (rc) {
		dev_err(ctx->dev, "PHY initialize failed %d\n", rc);
		return rc;
	}


	if (!IS_ERR(ctx->clk)) {

		clk_prepare_enable(ctx->clk);
		clk_disable_unprepare(ctx->clk);
		clk_prepare_enable(ctx->clk);
	}


	for (i = 0; i < MAX_LANE; i++)
		xgene_phy_gen_avg_val(ctx, i);

	dev_dbg(ctx->dev, "PHY initialized\n");
	return 0;
}
