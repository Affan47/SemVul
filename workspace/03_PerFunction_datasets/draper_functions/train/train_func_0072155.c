tegra_spi_start_transfer_one(struct spi_device *spi,
		struct spi_transfer *t, u32 command1)
{
	struct tegra_spi_data *tspi = spi_master_get_devdata(spi->master);
	unsigned total_fifo_words;
	int ret;

	total_fifo_words = tegra_spi_calculate_curr_xfer_param(spi, tspi, t);

	if (tspi->is_packed)
		command1 |= SPI_PACKED;

	command1 &= ~(SPI_CS_SEL_MASK | SPI_TX_EN | SPI_RX_EN);
	tspi->cur_direction = 0;
	if (t->rx_buf) {
		command1 |= SPI_RX_EN;
		tspi->cur_direction |= DATA_DIR_RX;
	}
	if (t->tx_buf) {
		command1 |= SPI_TX_EN;
		tspi->cur_direction |= DATA_DIR_TX;
	}
	command1 |= SPI_CS_SEL(spi->chip_select);
	tegra_spi_writel(tspi, command1, SPI_COMMAND1);
	tspi->command1_reg = command1;

	dev_dbg(tspi->dev, "The def 0x%x and written 0x%x\n",
		tspi->def_command1_reg, (unsigned)command1);

	if (total_fifo_words > SPI_FIFO_DEPTH)
		ret = tegra_spi_start_dma_based_transfer(tspi, t);
	else
		ret = tegra_spi_start_cpu_based_transfer(tspi, t);
	return ret;
}
