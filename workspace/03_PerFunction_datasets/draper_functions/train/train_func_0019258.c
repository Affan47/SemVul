dwc2_fs_phy_init(struct dwc2_hsotg *hsotg, bool select_phy)
{
	u32 usbcfg, i2cctl;
	int retval = 0;


	if (select_phy) {
		dev_dbg(hsotg->dev, "FS PHY selected\n");
		usbcfg = dwc2_readl(hsotg->regs + GUSBCFG);
		usbcfg |= GUSBCFG_PHYSEL;
		dwc2_writel(usbcfg, hsotg->regs + GUSBCFG);


		retval = dwc2_core_reset(hsotg);
		if (retval) {
			dev_err(hsotg->dev, "%s() Reset failed, aborting",
					__func__);
			return retval;
		}
	}


	if (dwc2_is_host_mode(hsotg))
		dwc2_init_fs_ls_pclk_sel(hsotg);

	if (hsotg->core_params->i2c_enable > 0) {
		dev_dbg(hsotg->dev, "FS PHY enabling I2C\n");


		usbcfg = dwc2_readl(hsotg->regs + GUSBCFG);
		usbcfg |= GUSBCFG_OTG_UTMI_FS_SEL;
		dwc2_writel(usbcfg, hsotg->regs + GUSBCFG);


		i2cctl = dwc2_readl(hsotg->regs + GI2CCTL);
		i2cctl &= ~GI2CCTL_I2CDEVADDR_MASK;
		i2cctl |= 1 << GI2CCTL_I2CDEVADDR_SHIFT;
		i2cctl &= ~GI2CCTL_I2CEN;
		dwc2_writel(i2cctl, hsotg->regs + GI2CCTL);
		i2cctl |= GI2CCTL_I2CEN;
		dwc2_writel(i2cctl, hsotg->regs + GI2CCTL);
	}

	return retval;
}
