fwtty_emit_breaks(struct work_struct *work)
{
	struct fwtty_port *port = to_port(to_delayed_work(work), emit_breaks);
	static const char buf[16];
	unsigned long now = jiffies;
	unsigned long elapsed = now - port->break_last;
	int n, t, c, brk = 0;


	n = (elapsed * port->cps) / HZ + 1;
	port->break_last = now;

	fwtty_dbg(port, "sending %d brks\n", n);

	while (n) {
		t = min(n, 16);
		c = tty_insert_flip_string_fixed_flag(&port->port, buf,
						      TTY_BREAK, t);
		n -= c;
		brk += c;
		if (c < t)
			break;
	}
	tty_flip_buffer_push(&port->port);

	if (port->mstatus & (UART_LSR_BI << 24))
		schedule_delayed_work(&port->emit_breaks, FREQ_BREAKS);
	port->icount.brk += brk;
}
