ftdi_process_packet(struct usb_serial_port *port,
		struct ftdi_private *priv, char *packet, int len)
{
	int i;
	char status;
	char flag;
	char *ch;

	if (len < 2) {
		dev_dbg(&port->dev, "malformed packet\n");
		return 0;
	}


	status = packet[0] & FTDI_STATUS_B0_MASK;
	if (status != priv->prev_status) {
		char diff_status = status ^ priv->prev_status;

		if (diff_status & FTDI_RS0_CTS)
			port->icount.cts++;
		if (diff_status & FTDI_RS0_DSR)
			port->icount.dsr++;
		if (diff_status & FTDI_RS0_RI)
			port->icount.rng++;
		if (diff_status & FTDI_RS0_RLSD) {
			struct tty_struct *tty;

			port->icount.dcd++;
			tty = tty_port_tty_get(&port->port);
			if (tty)
				usb_serial_handle_dcd_change(port, tty,
						status & FTDI_RS0_RLSD);
			tty_kref_put(tty);
		}

		wake_up_interruptible(&port->port.delta_msr_wait);
		priv->prev_status = status;
	}


	if (packet[1] & FTDI_RS_TEMT)
		priv->transmit_empty = 1;
	else
		priv->transmit_empty = 0;

	len -= 2;
	if (!len)
		return 0;


	flag = TTY_NORMAL;
	if (packet[1] & FTDI_RS_ERR_MASK) {


		if (packet[1] & FTDI_RS_BI) {
			flag = TTY_BREAK;
			port->icount.brk++;
			usb_serial_handle_break(port);
		} else if (packet[1] & FTDI_RS_PE) {
			flag = TTY_PARITY;
			port->icount.parity++;
		} else if (packet[1] & FTDI_RS_FE) {
			flag = TTY_FRAME;
			port->icount.frame++;
		}

		if (packet[1] & FTDI_RS_OE) {
			port->icount.overrun++;
			tty_insert_flip_char(&port->port, 0, TTY_OVERRUN);
		}
	}

	port->icount.rx += len;
	ch = packet + 2;

	if (port->port.console && port->sysrq) {
		for (i = 0; i < len; i++, ch++) {
			if (!usb_serial_handle_sysrq_char(port, *ch))
				tty_insert_flip_char(&port->port, *ch, flag);
		}
	} else {
		tty_insert_flip_string_fixed_flag(&port->port, ch, flag, len);
	}

	return len;
}
