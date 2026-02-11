lpuart_start_tx(struct uart_port *port)
{
	struct lpuart_port *sport = container_of(port,
			struct lpuart_port, port);
	struct circ_buf *xmit = &sport->port.state->xmit;
	unsigned char temp;

	temp = readb(port->membase + UARTCR2);
	writeb(temp | UARTCR2_TIE, port->membase + UARTCR2);

	if (sport->lpuart_dma_tx_use) {
		if (!uart_circ_empty(xmit) && !sport->dma_tx_in_progress)
			lpuart_prepare_tx(sport);
	} else {
		if (readb(port->membase + UARTSR1) & UARTSR1_TDRE)
			lpuart_transmit_buffer(sport);
	}
}
