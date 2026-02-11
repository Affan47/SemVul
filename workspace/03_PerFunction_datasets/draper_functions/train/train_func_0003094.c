dwmac100_dma_init(void __iomem *ioaddr, int pbl, int fb, int mb,
			     int burst_len, u32 dma_tx, u32 dma_rx, int atds)
{
	u32 value = readl(ioaddr + DMA_BUS_MODE);
	int limit;


	value |= DMA_BUS_MODE_SFT_RESET;
	writel(value, ioaddr + DMA_BUS_MODE);
	limit = 10;
	while (limit--) {
		if (!(readl(ioaddr + DMA_BUS_MODE) & DMA_BUS_MODE_SFT_RESET))
			break;
		mdelay(10);
	}
	if (limit < 0)
		return -EBUSY;


	writel(DMA_BUS_MODE_DEFAULT | (pbl << DMA_BUS_MODE_PBL_SHIFT),
	       ioaddr + DMA_BUS_MODE);


	writel(DMA_INTR_DEFAULT_MASK, ioaddr + DMA_INTR_ENA);


	writel(dma_tx, ioaddr + DMA_TX_BASE_ADDR);
	writel(dma_rx, ioaddr + DMA_RCV_BASE_ADDR);

	return 0;
}
