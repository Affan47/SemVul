sxgbe_sw_reset(void __iomem *addr)
{
	int retry_count = 10;

	writel(SXGBE_DMA_SOFT_RESET, addr + SXGBE_DMA_MODE_REG);
	while (retry_count--) {
		if (!(readl(addr + SXGBE_DMA_MODE_REG) &
		      SXGBE_DMA_SOFT_RESET))
			break;
		mdelay(10);
	}

	if (retry_count < 0)
		return -EBUSY;

	return 0;
}
