sci_er_interrupt(int irq, void *ptr)
{
	struct uart_port *port = ptr;
	struct sci_port *s = to_sci_port(port);


	if (port->type == PORT_SCI) {
		if (sci_handle_errors(port)) {

			serial_port_in(port, SCxSR);
			sci_clear_SCxSR(port, SCxSR_RDxF_CLEAR(port));
		}
	} else {
		sci_handle_fifo_overrun(port);
		if (!s->chan_rx)
			sci_receive_chars(ptr);
	}

	sci_clear_SCxSR(port, SCxSR_ERROR_CLEAR(port));


	if (!s->chan_tx)
		sci_tx_interrupt(irq, ptr);

	return IRQ_HANDLED;
}
