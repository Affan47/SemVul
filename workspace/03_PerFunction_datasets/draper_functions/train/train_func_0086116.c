sci_remap_port(struct uart_port *port)
{
	struct sci_port *sport = to_sci_port(port);


	if (port->membase)
		return 0;

	if (port->flags & UPF_IOREMAP) {
		port->membase = ioremap_nocache(port->mapbase, sport->reg_size);
		if (unlikely(!port->membase)) {
			dev_err(port->dev, "can't remap port#%d\n", port->line);
			return -ENXIO;
		}
	} else {


		port->membase = (void __iomem *)(uintptr_t)port->mapbase;
	}

	return 0;
}
