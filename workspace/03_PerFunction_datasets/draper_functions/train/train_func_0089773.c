intel_lpss_ltr_set(struct device *dev, s32 val)
{
	struct intel_lpss *lpss = dev_get_drvdata(dev);
	u32 ltr;


	ltr = readl(lpss->priv + LPSS_PRIV_ACTIVELTR);

	if (val == PM_QOS_LATENCY_ANY || val < 0) {
		ltr &= ~LPSS_PRIV_LTR_REQ;
	} else {
		ltr |= LPSS_PRIV_LTR_REQ;
		ltr &= ~LPSS_PRIV_LTR_SCALE_MASK;
		ltr &= ~LPSS_PRIV_LTR_VALUE_MASK;

		if (val > LPSS_PRIV_LTR_VALUE_MASK)
			ltr |= LPSS_PRIV_LTR_SCALE_32US | val >> 5;
		else
			ltr |= LPSS_PRIV_LTR_SCALE_1US | val;
	}

	if (ltr == lpss->active_ltr)
		return;

	writel(ltr, lpss->priv + LPSS_PRIV_ACTIVELTR);
	writel(ltr, lpss->priv + LPSS_PRIV_IDLELTR);


	intel_lpss_cache_ltr(lpss);
}
