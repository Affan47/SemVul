wl1251_spi_write(struct wl1251 *wl, int addr, void *buf,
			     size_t len)
{
	struct spi_transfer t[2];
	struct spi_message m;
	u32 *cmd;

	cmd = &wl->buffer_cmd;

	*cmd = 0;
	*cmd |= WSPI_CMD_WRITE;
	*cmd |= (len << WSPI_CMD_BYTE_LENGTH_OFFSET) & WSPI_CMD_BYTE_LENGTH;
	*cmd |= addr & WSPI_CMD_BYTE_ADDR;

	spi_message_init(&m);
	memset(t, 0, sizeof(t));

	t[0].tx_buf = cmd;
	t[0].len = sizeof(*cmd);
	spi_message_add_tail(&t[0], &m);

	t[1].tx_buf = buf;
	t[1].len = len;
	spi_message_add_tail(&t[1], &m);

	spi_sync(wl_to_spi(wl), &m);

	wl1251_dump(DEBUG_SPI, "spi_write cmd -> ", cmd, sizeof(*cmd));
	wl1251_dump(DEBUG_SPI, "spi_write buf -> ", buf, len);
}
