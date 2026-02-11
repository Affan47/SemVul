spi_read_op(struct enc28j60_net *priv, u8 op,
			   u8 addr)
{
	u8 tx_buf[2];
	u8 rx_buf[4];
	u8 val = 0;
	int ret;
	int slen = SPI_OPLEN;


	if (addr & SPRD_MASK)
		slen++;

	tx_buf[0] = op | (addr & ADDR_MASK);
	ret = spi_write_then_read(priv->spi, tx_buf, 1, rx_buf, slen);
	if (ret)
		printk(KERN_DEBUG DRV_NAME ": %s() failed: ret = %d\n",
			__func__, ret);
	else
		val = rx_buf[slen - 1];

	return val;
}
