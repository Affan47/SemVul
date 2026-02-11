xgene_phy_cfg_cmu_clk_type(struct xgene_phy_ctx *ctx,
				       enum cmu_type_t cmu_type,
				       enum clk_type_t clk_type)
{
	u32 val;


	cmu_rd(ctx, cmu_type, CMU_REG12, &val);
	val = CMU_REG12_STATE_DELAY9_SET(val, 0x1);
	cmu_wr(ctx, cmu_type, CMU_REG12, val);

	cmu_wr(ctx, cmu_type, CMU_REG13, 0x0222);
	cmu_wr(ctx, cmu_type, CMU_REG14, 0x2225);


	if (clk_type == CLK_EXT_DIFF) {

		cmu_rd(ctx, cmu_type, CMU_REG0, &val);
		val = CMU_REG0_PLL_REF_SEL_SET(val, 0x0);
		cmu_wr(ctx, cmu_type, CMU_REG0, val);

		cmu_rd(ctx, cmu_type, CMU_REG1, &val);
		val = CMU_REG1_REFCLK_CMOS_SEL_SET(val, 0x0);
		cmu_wr(ctx, cmu_type, CMU_REG1, val);
		dev_dbg(ctx->dev, "Set external reference clock\n");
	} else if (clk_type == CLK_INT_DIFF) {

		cmu_rd(ctx, cmu_type, CMU_REG0, &val);
		val = CMU_REG0_PLL_REF_SEL_SET(val, 0x1);
		cmu_wr(ctx, cmu_type, CMU_REG0, val);

		cmu_rd(ctx, cmu_type, CMU_REG1, &val);
		val = CMU_REG1_REFCLK_CMOS_SEL_SET(val, 0x1);
		cmu_wr(ctx, cmu_type, CMU_REG1, val);
		dev_dbg(ctx->dev, "Set internal reference clock\n");
	} else if (clk_type == CLK_INT_SING) {


		cmu_rd(ctx, cmu_type, CMU_REG1, &val);
		val = CMU_REG1_REFCLK_CMOS_SEL_SET(val, 0x1);
		cmu_wr(ctx, cmu_type, CMU_REG1, val);

		cmu_rd(ctx, cmu_type, CMU_REG1, &val);
		val = CMU_REG1_REFCLK_CMOS_SEL_SET(val, 0x0);
		cmu_wr(ctx, cmu_type, CMU_REG1, val);
		dev_dbg(ctx->dev,
			"Set internal single ended reference clock\n");
	}
}
