dw_mci_exynos_set_clksmpl(struct dw_mci *host, u8 sample)
{
	u32 clksel;
	struct dw_mci_exynos_priv_data *priv = host->priv;

	if (priv->ctrl_type == DW_MCI_TYPE_EXYNOS7 ||
		priv->ctrl_type == DW_MCI_TYPE_EXYNOS7_SMU)
		clksel = mci_readl(host, CLKSEL64);
	else
		clksel = mci_readl(host, CLKSEL);
	clksel = SDMMC_CLKSEL_UP_SAMPLE(clksel, sample);
	if (priv->ctrl_type == DW_MCI_TYPE_EXYNOS7 ||
		priv->ctrl_type == DW_MCI_TYPE_EXYNOS7_SMU)
		mci_writel(host, CLKSEL64, clksel);
	else
		mci_writel(host, CLKSEL, clksel);
}
