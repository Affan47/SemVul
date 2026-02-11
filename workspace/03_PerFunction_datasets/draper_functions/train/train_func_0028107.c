rp2_rx_chars(struct rp2_uart_port *up)
{
	u16 bytes = readw(up->base + RP2_RX_FIFO_COUNT);
	struct tty_port *port = &up->port.state->port;

	for (; bytes != 0; bytes--) {
		u32 byte = readw(up->base + RP2_DATA_BYTE) | RP2_DUMMY_READ;
		char ch = byte & 0xff;

		if (likely(!(byte & RP2_DATA_BYTE_EXCEPTION_MASK))) {
			if (!uart_handle_sysrq_char(&up->port, ch))
				uart_insert_char(&up->port, byte, 0, ch,
						 TTY_NORMAL);
		} else {
			char flag = TTY_NORMAL;

			if (byte & RP2_DATA_BYTE_BREAK_m)
				flag = TTY_BREAK;
			else if (byte & RP2_DATA_BYTE_ERR_FRAMING_m)
				flag = TTY_FRAME;
			else if (byte & RP2_DATA_BYTE_ERR_PARITY_m)
				flag = TTY_PARITY;
			uart_insert_char(&up->port, byte,
					 RP2_DATA_BYTE_ERR_OVERRUN_m, ch, flag);
		}
		up->port.icount.rx++;
	}

	spin_unlock(&up->port.lock);
	tty_flip_buffer_push(port);
	spin_lock(&up->port.lock);
}
