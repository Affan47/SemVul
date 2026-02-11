tegra_sflash_isr(int irq, void *context_data)
{
	struct tegra_sflash_data *tsd = context_data;

	tsd->status_reg = tegra_sflash_readl(tsd, SPI_STATUS);
	if (tsd->cur_direction & DATA_DIR_TX)
		tsd->tx_status = tsd->status_reg & SPI_TX_OVF;

	if (tsd->cur_direction & DATA_DIR_RX)
		tsd->rx_status = tsd->status_reg & SPI_RX_UNF;
	tegra_sflash_clear_status(tsd);

	return handle_cpu_based_xfer(tsd);
}
