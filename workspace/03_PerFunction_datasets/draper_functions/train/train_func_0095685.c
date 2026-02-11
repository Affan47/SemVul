dw_dma_tasklet(unsigned long data)
{
	struct dw_dma *dw = (struct dw_dma *)data;
	struct dw_dma_chan *dwc;
	u32 status_block;
	u32 status_xfer;
	u32 status_err;
	int i;

	status_block = dma_readl(dw, RAW.BLOCK);
	status_xfer = dma_readl(dw, RAW.XFER);
	status_err = dma_readl(dw, RAW.ERROR);

	dev_vdbg(dw->dma.dev, "%s: status_err=%x\n", __func__, status_err);

	for (i = 0; i < dw->dma.chancnt; i++) {
		dwc = &dw->chan[i];
		if (test_bit(DW_DMA_IS_CYCLIC, &dwc->flags))
			dwc_handle_cyclic(dw, dwc, status_block, status_err,
					status_xfer);
		else if (status_err & (1 << i))
			dwc_handle_error(dw, dwc);
		else if (status_xfer & (1 << i))
			dwc_scan_descriptors(dw, dwc);
	}


	channel_set_bit(dw, MASK.XFER, dw->all_chan_mask);
	channel_set_bit(dw, MASK.ERROR, dw->all_chan_mask);
}
