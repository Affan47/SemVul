sdio_clear_int(void)
{
#ifndef WILC_SDIO_IRQ_GPIO

	sdio_cmd52_t cmd;

	cmd.read_write = 0;
	cmd.function = 1;
	cmd.raw = 0;
	cmd.address = 0x4;
	cmd.data = 0;
	g_sdio.sdio_cmd52(&cmd);

	return cmd.data;
#else
	u32 reg;

	if (!sdio_read_reg(WILC_HOST_RX_CTRL_0, &reg)) {
		g_sdio.dPrint(N_ERR, "[wilc spi]: Failed read reg (%08x)...\n", WILC_HOST_RX_CTRL_0);
		return 0;
	}
	reg &= ~0x1;
	sdio_write_reg(WILC_HOST_RX_CTRL_0, reg);
	return 1;
#endif

}
