tegra_spi_writel(struct tegra_spi_data *tspi,
		u32 val, unsigned long reg)
{
	writel(val, tspi->base + reg);


	if (reg != SPI_TX_FIFO)
		readl(tspi->base + SPI_COMMAND1);
}
