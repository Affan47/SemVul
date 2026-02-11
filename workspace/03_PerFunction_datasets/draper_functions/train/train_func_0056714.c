sci_clear_SCxSR(struct uart_port *port, unsigned int mask)
{
	if (port->type == PORT_SCI) {

		serial_port_out(port, SCxSR, mask);
	} else if (to_sci_port(port)->overrun_mask == SCIFA_ORER) {


		serial_port_out(port, SCxSR,
				serial_port_in(port, SCxSR) & mask);
	} else {

		serial_port_out(port, SCxSR, mask & ~(SCIF_FERC | SCIF_PERC));
	}
}
