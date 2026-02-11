sccnxp_tx_empty(struct uart_port *port)
{
	u8 val;
	unsigned long flags;
	struct sccnxp_port *s = dev_get_drvdata(port->dev);

	spin_lock_irqsave(&s->lock, flags);
	val = sccnxp_port_read(port, SCCNXP_SR_REG);
	spin_unlock_irqrestore(&s->lock, flags);

	return (val & SR_TXEMT) ? TIOCSER_TEMT : 0;
}
