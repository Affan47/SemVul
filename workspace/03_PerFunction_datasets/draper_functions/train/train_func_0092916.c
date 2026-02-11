_dma_descriptor_align(struct dma_info *di)
{
	u32 addrl;


	if (di->d64txregbase != 0) {
		bcma_write32(di->core, DMA64TXREGOFFS(di, addrlow), 0xff0);
		addrl = bcma_read32(di->core, DMA64TXREGOFFS(di, addrlow));
		if (addrl != 0)
			return false;
	} else if (di->d64rxregbase != 0) {
		bcma_write32(di->core, DMA64RXREGOFFS(di, addrlow), 0xff0);
		addrl = bcma_read32(di->core, DMA64RXREGOFFS(di, addrlow));
		if (addrl != 0)
			return false;
	}
	return true;
}
