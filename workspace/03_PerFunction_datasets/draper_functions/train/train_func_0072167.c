gem_init_dma(struct gem *gp)
{
	u64 desc_dma = (u64) gp->gblock_dvma;
	u32 val;

	val = (TXDMA_CFG_BASE | (0x7ff << 10) | TXDMA_CFG_PMODE);
	writel(val, gp->regs + TXDMA_CFG);

	writel(desc_dma >> 32, gp->regs + TXDMA_DBHI);
	writel(desc_dma & 0xffffffff, gp->regs + TXDMA_DBLOW);
	desc_dma += (INIT_BLOCK_TX_RING_SIZE * sizeof(struct gem_txd));

	writel(0, gp->regs + TXDMA_KICK);

	val = (RXDMA_CFG_BASE | (RX_OFFSET << 10) |
	       ((14 / 2) << 13) | RXDMA_CFG_FTHRESH_128);
	writel(val, gp->regs + RXDMA_CFG);

	writel(desc_dma >> 32, gp->regs + RXDMA_DBHI);
	writel(desc_dma & 0xffffffff, gp->regs + RXDMA_DBLOW);

	writel(RX_RING_SIZE - 4, gp->regs + RXDMA_KICK);

	val  = (((gp->rx_pause_off / 64) << 0) & RXDMA_PTHRESH_OFF);
	val |= (((gp->rx_pause_on / 64) << 12) & RXDMA_PTHRESH_ON);
	writel(val, gp->regs + RXDMA_PTHRESH);

	if (readl(gp->regs + GREG_BIFCFG) & GREG_BIFCFG_M66EN)
		writel(((5 & RXDMA_BLANK_IPKTS) |
			((8 << 12) & RXDMA_BLANK_ITIME)),
		       gp->regs + RXDMA_BLANK);
	else
		writel(((5 & RXDMA_BLANK_IPKTS) |
			((4 << 12) & RXDMA_BLANK_ITIME)),
		       gp->regs + RXDMA_BLANK);
}
