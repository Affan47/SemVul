dma_txsuspended(struct dma_pub *pub)
{
	struct dma_info *di = container_of(pub, struct dma_info, dma);

	return (di->ntxd == 0) ||
	       ((bcma_read32(di->core,
			     DMA64TXREGOFFS(di, control)) & D64_XC_SE) ==
		D64_XC_SE);
}
