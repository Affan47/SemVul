spi_init(wilc_wlan_inp_t *inp, wilc_debug_func func)
{
	u32 reg;
	u32 chipid;

	static int isinit;

	if (isinit) {

		if (!spi_read_reg(0x1000, &chipid)) {
			PRINT_ER("[wilc spi]: Fail cmd read chip id...\n");
			return 0;
		}
		return 1;
	}

	memset(&g_spi, 0, sizeof(wilc_spi_t));

	g_spi.dPrint = func;
	g_spi.os_context = inp->os_context.os_private;
	if (inp->io_func.io_init) {
		if (!inp->io_func.io_init(g_spi.os_context)) {
			PRINT_ER("[wilc spi]: Failed io init bus...\n");
			return 0;
		}
	} else {
		return 0;
	}
	g_spi.spi_tx = inp->io_func.u.spi.spi_tx;
	g_spi.spi_rx = inp->io_func.u.spi.spi_rx;
	g_spi.spi_trx = inp->io_func.u.spi.spi_trx;
	g_spi.spi_max_speed = inp->io_func.u.spi.spi_max_speed;


	g_spi.crc_off = 0;


	if (!spi_internal_read(WILC_SPI_PROTOCOL_OFFSET, &reg)) {


		g_spi.crc_off = 1;
		PRINT_ER("[wilc spi]: Failed internal read protocol with CRC on, retyring with CRC off...\n");
		if (!spi_internal_read(WILC_SPI_PROTOCOL_OFFSET, &reg)) {

			PRINT_ER("[wilc spi]: Failed internal read protocol...\n");
			return 0;
		}
	}
	if (g_spi.crc_off == 0)	{
		reg &= ~0xc;
		reg &= ~0x70;
		reg |= (0x5 << 4);
		if (!spi_internal_write(WILC_SPI_PROTOCOL_OFFSET, reg)) {
			PRINT_ER("[wilc spi %d]: Failed internal write protocol reg...\n", __LINE__);
			return 0;
		}
		g_spi.crc_off = 1;
	}


	if (!spi_read_reg(0x1000, &chipid)) {
		PRINT_ER("[wilc spi]: Fail cmd read chip id...\n");
		return 0;
	}


	g_spi.has_thrpt_enh = 1;

	isinit = 1;

	return 1;
}
