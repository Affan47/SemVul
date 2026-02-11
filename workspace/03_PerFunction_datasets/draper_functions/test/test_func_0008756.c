asc_interrupt(int irq, void *ptr)
{
	struct uart_port *port = ptr;
	u32 status;

	spin_lock(&port->lock);

	status = asc_in(port, ASC_STA);

	if (status & ASC_STA_RBF) {

		asc_receive_chars(port);
	}

	if ((status & ASC_STA_THE) &&
	    (asc_in(port, ASC_INTEN) & ASC_INTEN_THE)) {

		asc_transmit_chars(port);
	}

	spin_unlock(&port->lock);

	return IRQ_HANDLED;
}
