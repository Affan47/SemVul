atmel_rx_from_pdc(struct uart_port *port)
{
	struct atmel_uart_port *atmel_port = to_atmel_uart_port(port);
	struct tty_port *tport = &port->state->port;
	struct atmel_dma_buffer *pdc;
	int rx_idx = atmel_port->pdc_rx_idx;
	unsigned int head;
	unsigned int tail;
	unsigned int count;

	do {

		atmel_uart_writel(port, ATMEL_US_CR, ATMEL_US_STTTO);

		pdc = &atmel_port->pdc_rx[rx_idx];
		head = atmel_uart_readl(port, ATMEL_PDC_RPR) - pdc->dma_addr;
		tail = pdc->ofs;


		head = min(head, pdc->dma_size);

		if (likely(head != tail)) {
			dma_sync_single_for_cpu(port->dev, pdc->dma_addr,
					pdc->dma_size, DMA_FROM_DEVICE);


			count = head - tail;

			tty_insert_flip_string(tport, pdc->buf + pdc->ofs,
						count);

			dma_sync_single_for_device(port->dev, pdc->dma_addr,
					pdc->dma_size, DMA_FROM_DEVICE);

			port->icount.rx += count;
			pdc->ofs = head;
		}


		if (head >= pdc->dma_size) {
			pdc->ofs = 0;
			atmel_uart_writel(port, ATMEL_PDC_RNPR, pdc->dma_addr);
			atmel_uart_writel(port, ATMEL_PDC_RNCR, pdc->dma_size);

			rx_idx = !rx_idx;
			atmel_port->pdc_rx_idx = rx_idx;
		}
	} while (head >= pdc->dma_size);


	spin_unlock(&port->lock);
	tty_flip_buffer_push(tport);
	spin_lock(&port->lock);

	atmel_uart_writel(port, ATMEL_US_IER,
			  ATMEL_US_ENDRX | ATMEL_US_TIMEOUT);
}
