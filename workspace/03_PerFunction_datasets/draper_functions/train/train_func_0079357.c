pch_uart_hal_write(struct eg20t_port *priv,
			      const unsigned char *buf, int tx_size)
{
	int i;
	unsigned int thr;

	for (i = 0; i < tx_size;) {
		thr = buf[i++];
		iowrite8(thr, priv->membase + PCH_UART_THR);
	}
}
