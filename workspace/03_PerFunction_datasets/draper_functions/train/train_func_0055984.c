set_modem_info(struct moschip_port *mos7720_port, unsigned int cmd,
			  unsigned int __user *value)
{
	unsigned int mcr;
	unsigned int arg;

	struct usb_serial_port *port;

	if (mos7720_port == NULL)
		return -1;

	port = (struct usb_serial_port *)mos7720_port->port;
	mcr = mos7720_port->shadowMCR;

	if (copy_from_user(&arg, value, sizeof(int)))
		return -EFAULT;

	switch (cmd) {
	case TIOCMBIS:
		if (arg & TIOCM_RTS)
			mcr |= UART_MCR_RTS;
		if (arg & TIOCM_DTR)
			mcr |= UART_MCR_RTS;
		if (arg & TIOCM_LOOP)
			mcr |= UART_MCR_LOOP;
		break;

	case TIOCMBIC:
		if (arg & TIOCM_RTS)
			mcr &= ~UART_MCR_RTS;
		if (arg & TIOCM_DTR)
			mcr &= ~UART_MCR_RTS;
		if (arg & TIOCM_LOOP)
			mcr &= ~UART_MCR_LOOP;
		break;

	}

	mos7720_port->shadowMCR = mcr;
	write_mos_reg(port->serial, port->port_number, MOS7720_MCR,
		      mos7720_port->shadowMCR);

	return 0;
}
