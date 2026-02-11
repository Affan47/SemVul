fimc_hw_set_effect(struct fimc_ctx *ctx)
{
	struct fimc_dev *dev = ctx->fimc_dev;
	struct fimc_effect *effect = &ctx->effect;
	u32 cfg = 0;

	if (effect->type != FIMC_REG_CIIMGEFF_FIN_BYPASS) {
		cfg |= FIMC_REG_CIIMGEFF_IE_SC_AFTER |
			FIMC_REG_CIIMGEFF_IE_ENABLE;
		cfg |= effect->type;
		if (effect->type == FIMC_REG_CIIMGEFF_FIN_ARBITRARY)
			cfg |= (effect->pat_cb << 13) | effect->pat_cr;
	}

	writel(cfg, dev->regs + FIMC_REG_CIIMGEFF);
}
