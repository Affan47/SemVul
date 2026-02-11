dwc2_gahbcfg_init(struct dwc2_hsotg *hsotg)
{
	u32 ahbcfg = dwc2_readl(hsotg->regs + GAHBCFG);

	switch (hsotg->hw_params.arch) {
	case GHWCFG2_EXT_DMA_ARCH:
		dev_err(hsotg->dev, "External DMA Mode not supported\n");
		return -EINVAL;

	case GHWCFG2_INT_DMA_ARCH:
		dev_dbg(hsotg->dev, "Internal DMA Mode\n");
		if (hsotg->core_params->ahbcfg != -1) {
			ahbcfg &= GAHBCFG_CTRL_MASK;
			ahbcfg |= hsotg->core_params->ahbcfg &
				  ~GAHBCFG_CTRL_MASK;
		}
		break;

	case GHWCFG2_SLAVE_ONLY_ARCH:
	default:
		dev_dbg(hsotg->dev, "Slave Only Mode\n");
		break;
	}

	dev_dbg(hsotg->dev, "dma_enable:%d dma_desc_enable:%d\n",
		hsotg->core_params->dma_enable,
		hsotg->core_params->dma_desc_enable);

	if (hsotg->core_params->dma_enable > 0) {
		if (hsotg->core_params->dma_desc_enable > 0)
			dev_dbg(hsotg->dev, "Using Descriptor DMA mode\n");
		else
			dev_dbg(hsotg->dev, "Using Buffer DMA mode\n");
	} else {
		dev_dbg(hsotg->dev, "Using Slave mode\n");
		hsotg->core_params->dma_desc_enable = 0;
	}

	if (hsotg->core_params->dma_enable > 0)
		ahbcfg |= GAHBCFG_DMA_EN;

	dwc2_writel(ahbcfg, hsotg->regs + GAHBCFG);

	return 0;
}
