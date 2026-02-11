sci_rx_dma_release(struct sci_port *s, bool enable_pio)
{
	struct dma_chan *chan = s->chan_rx;
	struct uart_port *port = &s->port;
	unsigned long flags;

	spin_lock_irqsave(&port->lock, flags);
	s->chan_rx = NULL;
	s->cookie_rx[0] = s->cookie_rx[1] = -EINVAL;
	spin_unlock_irqrestore(&port->lock, flags);
	dmaengine_terminate_all(chan);
	dma_free_coherent(chan->device->dev, s->buf_len_rx * 2, s->rx_buf[0],
			  sg_dma_address(&s->sg_rx[0]));
	dma_release_channel(chan);
	if (enable_pio)
		sci_start_rx(port);
}
