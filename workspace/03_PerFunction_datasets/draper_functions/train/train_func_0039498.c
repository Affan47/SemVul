tegra_spi_setup_transfer_one(struct spi_device *spi,
		struct spi_transfer *t, bool is_first_of_msg)
{
	struct tegra_spi_data *tspi = spi_master_get_devdata(spi->master);
	u32 speed = t->speed_hz;
	u8 bits_per_word = t->bits_per_word;
	u32 command1;
	int req_mode;

	if (speed != tspi->cur_speed) {
		clk_set_rate(tspi->clk, speed);
		tspi->cur_speed = speed;
	}

	tspi->cur_spi = spi;
	tspi->cur_pos = 0;
	tspi->cur_rx_pos = 0;
	tspi->cur_tx_pos = 0;
	tspi->curr_xfer = t;

	if (is_first_of_msg) {
		tegra_spi_clear_status(tspi);

		command1 = tspi->def_command1_reg;
		command1 |= SPI_BIT_LENGTH(bits_per_word - 1);

		command1 &= ~SPI_CONTROL_MODE_MASK;
		req_mode = spi->mode & 0x3;
		if (req_mode == SPI_MODE_0)
			command1 |= SPI_CONTROL_MODE_0;
		else if (req_mode == SPI_MODE_1)
			command1 |= SPI_CONTROL_MODE_1;
		else if (req_mode == SPI_MODE_2)
			command1 |= SPI_CONTROL_MODE_2;
		else if (req_mode == SPI_MODE_3)
			command1 |= SPI_CONTROL_MODE_3;

		if (tspi->cs_control) {
			if (tspi->cs_control != spi)
				tegra_spi_writel(tspi, command1, SPI_COMMAND1);
			tspi->cs_control = NULL;
		} else
			tegra_spi_writel(tspi, command1, SPI_COMMAND1);

		command1 |= SPI_CS_SW_HW;
		if (spi->mode & SPI_CS_HIGH)
			command1 |= SPI_CS_SS_VAL;
		else
			command1 &= ~SPI_CS_SS_VAL;

		tegra_spi_writel(tspi, 0, SPI_COMMAND2);
	} else {
		command1 = tspi->command1_reg;
		command1 &= ~SPI_BIT_LENGTH(~0);
		command1 |= SPI_BIT_LENGTH(bits_per_word - 1);
	}

	return command1;
}
