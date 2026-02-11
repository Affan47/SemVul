dw_mci_submit_data_dma(struct dw_mci *host, struct mmc_data *data)
{
	unsigned long irqflags;
	int sg_len;
	u32 temp;

	host->using_dma = 0;


	if (!host->use_dma)
		return -ENODEV;

	sg_len = dw_mci_pre_dma_transfer(host, data, 0);
	if (sg_len < 0) {
		host->dma_ops->stop(host);
		return sg_len;
	}

	host->using_dma = 1;

	if (host->use_dma == TRANS_MODE_IDMAC)
		dev_vdbg(host->dev,
			 "sd sg_cpu: %#lx sg_dma: %#lx sg_len: %d\n",
			 (unsigned long)host->sg_cpu,
			 (unsigned long)host->sg_dma,
			 sg_len);


	if (host->prev_blksz != data->blksz)
		dw_mci_adjust_fifoth(host, data);


	temp = mci_readl(host, CTRL);
	temp |= SDMMC_CTRL_DMA_ENABLE;
	mci_writel(host, CTRL, temp);


	spin_lock_irqsave(&host->irq_lock, irqflags);
	temp = mci_readl(host, INTMASK);
	temp  &= ~(SDMMC_INT_RXDR | SDMMC_INT_TXDR);
	mci_writel(host, INTMASK, temp);
	spin_unlock_irqrestore(&host->irq_lock, irqflags);

	if (host->dma_ops->start(host, sg_len)) {

		dev_err(host->dev, "%s: failed to start DMA.\n", __func__);
		return -ENODEV;
	}

	return 0;
}
