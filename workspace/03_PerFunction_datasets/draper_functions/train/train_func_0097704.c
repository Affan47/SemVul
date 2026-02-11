imx_phy_reg_write(u16 val, void __iomem *mmio)
{
	u32 crval = val;
	int ret;


	writel(crval, mmio + IMX_P0PHYCR);


	ret = imx_phy_crbit_assert(mmio, IMX_P0PHYCR_CR_CAP_DATA, true);
	if (ret)
		return ret;


	ret = imx_phy_crbit_assert(mmio, IMX_P0PHYCR_CR_CAP_DATA, false);
	if (ret)
		return ret;

	if (val & IMX_CLOCK_RESET_RESET) {


		crval |= IMX_P0PHYCR_CR_WRITE;
		writel(crval, mmio + IMX_P0PHYCR);
		goto out;
	}


	ret = imx_phy_crbit_assert(mmio, IMX_P0PHYCR_CR_WRITE, true);
	if (ret)
		return ret;


	ret = imx_phy_crbit_assert(mmio, IMX_P0PHYCR_CR_WRITE, false);
	if (ret)
		return ret;

out:
	return 0;
}
