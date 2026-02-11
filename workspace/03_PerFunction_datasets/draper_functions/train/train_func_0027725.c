cdv_init_pm(struct drm_device *dev)
{
	struct drm_psb_private *dev_priv = dev->dev_private;
	u32 pwr_cnt;
	int i;

	dev_priv->apm_base = CDV_MSG_READ32(PSB_PUNIT_PORT,
							PSB_APMBA) & 0xFFFF;
	dev_priv->ospm_base = CDV_MSG_READ32(PSB_PUNIT_PORT,
							PSB_OSPMBA) & 0xFFFF;


	pwr_cnt = inl(dev_priv->apm_base + PSB_APM_CMD);


	pwr_cnt &= ~PSB_PWRGT_GFX_MASK;
	pwr_cnt |= PSB_PWRGT_GFX_ON;
	outl(pwr_cnt, dev_priv->apm_base + PSB_APM_CMD);


	for (i = 0; i < 5; i++) {
		u32 pwr_sts = inl(dev_priv->apm_base + PSB_APM_STS);
		if ((pwr_sts & PSB_PWRGT_GFX_MASK) == 0)
			return;
		udelay(10);
	}
	dev_err(dev->dev, "GPU: power management timed out.\n");
}
