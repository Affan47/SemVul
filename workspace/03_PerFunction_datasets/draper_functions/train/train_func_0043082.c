sccnxp_type(struct uart_port *port)
{
	struct sccnxp_port *s = dev_get_drvdata(port->dev);

	return (port->type == PORT_SC26XX) ? s->chip->name : NULL;
}
