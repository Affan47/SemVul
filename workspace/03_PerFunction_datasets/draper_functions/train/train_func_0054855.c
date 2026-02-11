ili922x_write(struct spi_device *spi, u8 reg, u16 value)
{
	struct spi_message msg;
	struct spi_transfer xfer_regindex, xfer_regvalue;
	unsigned char tbuf[CMD_BUFSIZE];
	unsigned char rbuf[CMD_BUFSIZE];
	int ret, len = 0;

	memset(&xfer_regindex, 0, sizeof(struct spi_transfer));
	memset(&xfer_regvalue, 0, sizeof(struct spi_transfer));

	spi_message_init(&msg);
	xfer_regindex.tx_buf = tbuf;
	xfer_regindex.rx_buf = rbuf;
	xfer_regindex.cs_change = 1;
	CHECK_FREQ_REG(spi, &xfer_regindex);

	tbuf[0] = set_tx_byte(START_BYTE(ili922x_id, START_RS_INDEX,
					 START_RW_WRITE));
	tbuf[1] = set_tx_byte(0);
	tbuf[2] = set_tx_byte(reg);
	xfer_regindex.bits_per_word = 8;
	xfer_regindex.len = 3;
	spi_message_add_tail(&xfer_regindex, &msg);

	ret = spi_sync(spi, &msg);

	spi_message_init(&msg);
	len = 0;
	tbuf[0] = set_tx_byte(START_BYTE(ili922x_id, START_RS_REG,
					 START_RW_WRITE));
	tbuf[1] = set_tx_byte((value & 0xFF00) >> 8);
	tbuf[2] = set_tx_byte(value & 0x00FF);

	xfer_regvalue.cs_change = 1;
	xfer_regvalue.len = 3;
	xfer_regvalue.tx_buf = tbuf;
	xfer_regvalue.rx_buf = rbuf;
	CHECK_FREQ_REG(spi, &xfer_regvalue);

	spi_message_add_tail(&xfer_regvalue, &msg);

	ret = spi_sync(spi, &msg);
	if (ret < 0) {
		dev_err(&spi->dev, "Error sending SPI message 0x%x", ret);
		return ret;
	}
	return 0;
}
