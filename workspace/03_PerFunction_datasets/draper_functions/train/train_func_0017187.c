cc2520_cmd_strobe(struct cc2520_private *priv, u8 cmd)
{
	int ret;
	u8 status = 0xff;
	struct spi_message msg;
	struct spi_transfer xfer = {
		.len = 0,
		.tx_buf = priv->buf,
		.rx_buf = priv->buf,
	};

	spi_message_init(&msg);
	spi_message_add_tail(&xfer, &msg);

	mutex_lock(&priv->buffer_mutex);
	priv->buf[xfer.len++] = cmd;
	dev_vdbg(&priv->spi->dev,
		 "command strobe buf[0] = %02x\n",
		 priv->buf[0]);

	ret = spi_sync(priv->spi, &msg);
	if (!ret)
		status = priv->buf[0];
	dev_vdbg(&priv->spi->dev,
		 "buf[0] = %02x\n", priv->buf[0]);
	mutex_unlock(&priv->buffer_mutex);

	return ret;
}
