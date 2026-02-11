fotg210_enable_dma(struct fotg210_ep *ep,
			      dma_addr_t d, u32 len)
{
	u32 value;
	struct fotg210_udc *fotg210 = ep->fotg210;


	value = ioread32(fotg210->reg + FOTG210_DMACPSR1);
	value &= ~(DMACPSR1_DMA_LEN(0xFFFF) | DMACPSR1_DMA_TYPE(1));
	value |= DMACPSR1_DMA_LEN(len) | DMACPSR1_DMA_TYPE(ep->dir_in);
	iowrite32(value, fotg210->reg + FOTG210_DMACPSR1);


	value = ioread32(fotg210->reg + FOTG210_DMATFNR);
	if (ep->epnum)
		value |= DMATFNR_ACC_FN(ep->epnum - 1);
	else
		value |= DMATFNR_ACC_CXF;
	iowrite32(value, fotg210->reg + FOTG210_DMATFNR);


	iowrite32(d, fotg210->reg + FOTG210_DMACPSR2);


	value = ioread32(fotg210->reg + FOTG210_DMISGR2);
	value &= ~(DMISGR2_MDMA_CMPLT | DMISGR2_MDMA_ERROR);
	iowrite32(value, fotg210->reg + FOTG210_DMISGR2);


	value = ioread32(fotg210->reg + FOTG210_DMACPSR1);
	value |= DMACPSR1_DMA_START;
	iowrite32(value, fotg210->reg + FOTG210_DMACPSR1);
}
