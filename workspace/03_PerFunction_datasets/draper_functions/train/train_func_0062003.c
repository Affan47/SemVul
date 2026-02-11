mxser_activate(struct tty_port *port, struct tty_struct *tty)
{
	struct mxser_port *info = container_of(port, struct mxser_port, port);
	unsigned long page;
	unsigned long flags;

	page = __get_free_page(GFP_KERNEL);
	if (!page)
		return -ENOMEM;

	spin_lock_irqsave(&info->slock, flags);

	if (!info->ioaddr || !info->type) {
		set_bit(TTY_IO_ERROR, &tty->flags);
		free_page(page);
		spin_unlock_irqrestore(&info->slock, flags);
		return 0;
	}
	info->port.xmit_buf = (unsigned char *) page;


	if (info->board->chip_flag)
		outb((UART_FCR_CLEAR_RCVR |
			UART_FCR_CLEAR_XMIT |
			MOXA_MUST_FCR_GDA_MODE_ENABLE), info->ioaddr + UART_FCR);
	else
		outb((UART_FCR_CLEAR_RCVR | UART_FCR_CLEAR_XMIT),
			info->ioaddr + UART_FCR);


	if (inb(info->ioaddr + UART_LSR) == 0xff) {
		spin_unlock_irqrestore(&info->slock, flags);
		if (capable(CAP_SYS_ADMIN)) {
			set_bit(TTY_IO_ERROR, &tty->flags);
			return 0;
		} else
			return -ENODEV;
	}


	(void) inb(info->ioaddr + UART_LSR);
	(void) inb(info->ioaddr + UART_RX);
	(void) inb(info->ioaddr + UART_IIR);
	(void) inb(info->ioaddr + UART_MSR);


	outb(UART_LCR_WLEN8, info->ioaddr + UART_LCR);
	info->MCR = UART_MCR_DTR | UART_MCR_RTS;
	outb(info->MCR, info->ioaddr + UART_MCR);


	info->IER = UART_IER_MSI | UART_IER_RLSI | UART_IER_RDI;

	if (info->board->chip_flag)
		info->IER |= MOXA_MUST_IER_EGDAI;
	outb(info->IER, info->ioaddr + UART_IER);


	(void) inb(info->ioaddr + UART_LSR);
	(void) inb(info->ioaddr + UART_RX);
	(void) inb(info->ioaddr + UART_IIR);
	(void) inb(info->ioaddr + UART_MSR);

	clear_bit(TTY_IO_ERROR, &tty->flags);
	info->xmit_cnt = info->xmit_head = info->xmit_tail = 0;


	mxser_change_speed(tty, NULL);
	spin_unlock_irqrestore(&info->slock, flags);

	return 0;
}
