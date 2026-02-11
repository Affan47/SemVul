xgene_edac_l3_hw_init(struct edac_device_ctl_info *edac_dev,
				  bool enable)
{
	struct xgene_edac_dev_ctx *ctx = edac_dev->pvt_info;
	u32 val;

	val = readl(ctx->dev_csr + L3C_ECR);
	val |= L3C_UCERREN | L3C_CERREN;

	if (edac_dev->op_state == OP_RUNNING_INTERRUPT) {
		if (enable)
			val |= L3C_ECR_UCINTREN | L3C_ECR_CINTREN;
		else
			val &= ~(L3C_ECR_UCINTREN | L3C_ECR_CINTREN);
	}
	writel(val, ctx->dev_csr + L3C_ECR);

	if (edac_dev->op_state == OP_RUNNING_INTERRUPT) {

		if (enable) {
			xgene_edac_pcp_clrbits(ctx->edac, PCPHPERRINTMSK,
					       L3C_UNCORR_ERR_MASK);
			xgene_edac_pcp_clrbits(ctx->edac, PCPLPERRINTMSK,
					       L3C_CORR_ERR_MASK);
		} else {
			xgene_edac_pcp_setbits(ctx->edac, PCPHPERRINTMSK,
					       L3C_UNCORR_ERR_MASK);
			xgene_edac_pcp_setbits(ctx->edac, PCPLPERRINTMSK,
					       L3C_CORR_ERR_MASK);
		}
	}
}
