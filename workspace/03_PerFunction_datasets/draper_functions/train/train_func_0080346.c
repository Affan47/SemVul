zx_i2s_rx_dma_en(void __iomem *base, bool on)
{
	unsigned long val;

	val = readl_relaxed(base + ZX_I2S_FIFO_CTRL);
	val |= ZX_I2S_FIFO_CTRL_RX_RST | (I2S_DEAGULT_FIFO_THRES << 16);
	if (on)
		val |= ZX_I2S_FIFO_CTRL_RX_DMA_EN;
	else
		val &= ~ZX_I2S_FIFO_CTRL_RX_DMA_EN;
	writel_relaxed(val, base + ZX_I2S_FIFO_CTRL);
}
