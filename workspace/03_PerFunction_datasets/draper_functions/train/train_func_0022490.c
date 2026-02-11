sci_rxfill(struct uart_port *port)
{
	const struct plat_sci_reg *reg;

	reg = sci_getreg(port, SCRFDR);
	if (reg->size)
		return serial_port_in(port, SCRFDR) & ((port->fifosize << 1) - 1);

	reg = sci_getreg(port, SCFDR);
	if (reg->size)
		return serial_port_in(port, SCFDR) & ((port->fifosize << 1) - 1);

	return (serial_port_in(port, SCxSR) & SCxSR_RDxF(port)) != 0;
}
