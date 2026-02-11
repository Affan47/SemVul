wl12xx_spi_raw_write(struct device *child, int addr,
					     void *buf, size_t len, bool fixed)
{
	struct wl12xx_spi_glue *glue = dev_get_drvdata(child->parent);

	struct spi_transfer t[2 * WSPI_MAX_NUM_OF_CHUNKS];
	struct spi_message m;
	u32 commands[WSPI_MAX_NUM_OF_CHUNKS];
	u32 *cmd;
	u32 chunk_len;
	int i;

	WARN_ON(len > SPI_AGGR_BUFFER_SIZE);

	spi_message_init(&m);
	memset(t, 0, sizeof(t));

	cmd = &commands[0];
	i = 0;
	while (len > 0) {
		chunk_len = min_t(size_t, WSPI_MAX_CHUNK_SIZE, len);

		*cmd = 0;
		*cmd |= WSPI_CMD_WRITE;
		*cmd |= (chunk_len << WSPI_CMD_BYTE_LENGTH_OFFSET) &
			WSPI_CMD_BYTE_LENGTH;
		*cmd |= addr & WSPI_CMD_BYTE_ADDR;

		if (fixed)
			*cmd |= WSPI_CMD_FIXED;

		t[i].tx_buf = cmd;
		t[i].len = sizeof(*cmd);
		spi_message_add_tail(&t[i++], &m);

		t[i].tx_buf = buf;
		t[i].len = chunk_len;
		spi_message_add_tail(&t[i++], &m);

		if (!fixed)
			addr += chunk_len;
		buf += chunk_len;
		len -= chunk_len;
		cmd++;
	}

	spi_sync(to_spi_device(glue->dev), &m);

	return 0;
}
