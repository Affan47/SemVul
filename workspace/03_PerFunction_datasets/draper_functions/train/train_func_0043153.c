imx_rs485_config(struct uart_port *port,
			    struct serial_rs485 *rs485conf)
{
	struct imx_port *sport = (struct imx_port *)port;


	rs485conf->delay_rts_before_send = 0;
	rs485conf->delay_rts_after_send = 0;
	rs485conf->flags |= SER_RS485_RX_DURING_TX;


	if (!sport->have_rtscts)
		rs485conf->flags &= ~SER_RS485_ENABLED;

	if (rs485conf->flags & SER_RS485_ENABLED) {
		unsigned long temp;


		temp = readl(sport->port.membase + UCR2);
		temp &= ~UCR2_CTSC;
		if (rs485conf->flags & SER_RS485_RTS_AFTER_SEND)
			temp &= ~UCR2_CTS;
		else
			temp |= UCR2_CTS;
		writel(temp, sport->port.membase + UCR2);
	}

	port->rs485 = *rs485conf;

	return 0;
}
